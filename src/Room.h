/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 房间
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once

#include "Player.h"

#include <cstdint>
#include <vector>


struct Room {
    std::mutex mu; // 锁

    uint32_t seed; // 目前对局种子
    std::string id; // 目前对局信息

    std::vector<std::shared_ptr<Player>> player; // 游戏玩家
    std::vector<std::shared_ptr<Player>> sub;    // 观战玩家
};