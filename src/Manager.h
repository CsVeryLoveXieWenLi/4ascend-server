/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 管理
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once

#include "Room.h"

#include <string>
#include <unordered_map>


class Manager {
public:
    // 解析并且操作
    void parse() {

    };

private:
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;

    std::mutex mu;
};
