/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 玩家
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once

#include <cinatra/coro_http_connection.hpp>

#include <string>


struct Player {
    cinatra::coro_http_connection* client;

    std::string name;
    std::string uuid;
};