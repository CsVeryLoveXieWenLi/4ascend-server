/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 管理
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once

#include "Room.h"

#include <cinatra/coro_http_connection.hpp>

#include <memory>
#include <string>
#include <unordered_map>


class Manager {
public:
    // 创建房间
    bool room_create(std::string& id);

    // 加入房间（玩家）
    bool room_join(cinatra::coro_http_connection* c, std::string& id, std::string& name, std::string& uuidm);

    // 加入房间（观众）
    bool room_subscrib(cinatra::coro_http_connection* c, std::string& id, std::string& name, std::string& uuidm);


    // 消息转发（玩家互相）
    cinatra::coro_http_connection* room_pl2pl(std::string& id, std::string& uuidm);

    // 消息转发（玩家转观众）
    cinatra::coro_http_connection* room_pl2se(std::string& id, std::string& uuidm, std::string& uuidf);

    // 消息转发（观众转玩家）
    cinatra::coro_http_connection* room_se2pl(std::string& id, std::string& uuidm, std::string& uuidf);


private:
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;

    std::mutex mu;
};
