/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 管理
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#include "Manager.h"
#include "Room.h"

#include <cinatra/coro_http_connection.hpp>
#include <nlohmann/json.hpp>

#include <memory>
#include <string>


// 创建房间
void Manager::room_create(nlohmann::json& params, cinatra::coro_http_connection* client) {
    if (!params.contains("id")) return;
    auto id = params["id"].get<std::string>();

    mu.lock();
    auto inserted = rooms.try_emplace(id, std::make_shared<Room>()).second;
    mu.unlock();

    auto r                = nlohmann::json::object();
    r["op"]               = "room_create";
    r["result"]           = nlohmann::json::object();
    r["result"]["status"] = inserted;

    auto p = r.dump();
    client->write_websocket(p);
};