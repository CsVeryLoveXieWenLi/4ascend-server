/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 主入口
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#include <cinatra.hpp>


int main() {
    using namespace cinatra;

    coro_http_server server(1, 9001);
    server.set_http_handler<cinatra::GET>(
        "/ws_echo",
        [](coro_http_request& req, coro_http_response& resp) -> async_simple::coro::Lazy<void> {
            assert(req.get_content_type() == content_type::websocket);

            while (true) {
                auto result = co_await req.get_conn()->read_websocket();
                if (result.ec) {
                    break;
                }

                if (result.type == ws_frame_type::WS_CLOSE_FRAME) {
                    std::cout << "close frame\n";
                    break;
                }

                if (result.type == ws_frame_type::WS_TEXT_FRAME || result.type == ws_frame_type::WS_BINARY_FRAME) {
                    std::cout << result.data << "\n";

                } else if (result.type == ws_frame_type::WS_PING_FRAME || result.type == ws_frame_type::WS_PONG_FRAME) {
                    // ping pong frame just need to continue, no need echo anything,
                    // because framework has reply ping/pong msg to client
                    // automatically.
                    continue;
                } else {
                    // error frame
                    break;
                }

                auto ec = co_await req.get_conn()->write_websocket(result.data);
                if (ec) {
                    break;
                }
            }
        }
    );
}