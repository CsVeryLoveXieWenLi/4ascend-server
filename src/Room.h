/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 房间
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once

#include "Player.h"

#include <unordered_map>


struct Room {
    std::mutex mu;

    std::shared_ptr<Player> player1; // 玩家1
    std::shared_ptr<Player> player2; // 玩家2

    std::unordered_map<std::string, std::shared_ptr<Player>> subscriber; // 观战玩家
};