/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 管理
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#include "Manager.h"
#include "Room.h"

#include <cinatra/coro_http_connection.hpp>

#include <memory>
#include <string>


// 创建房间
bool Manager::room_create(std::string& id) {
    std::lock_guard<std::mutex> lock(this->mu);

    auto room     = std::make_shared<Room>();
    room->player1 = std::make_shared<Player>();
    room->player2 = std::make_shared<Player>();
    // room->subscriber.reserve(10);

    return rooms.try_emplace(std::string(id), room).second; // cp
};

// 加入房间（玩家）
bool Manager::room_join(cinatra::coro_http_connection* c, std::string& id, std::string& name, std::string& uuidm) {
    std::shared_ptr<Room> room;
    {
        std::lock_guard<std::mutex> lock(this->mu);
        auto                        it = rooms.find(id);
        if (it == rooms.end()) return false;
        room = it->second;
    }

    if (!room) return false; // null

    std::lock_guard<std::mutex> lock(room->mu);
    if (room->player1->uuid.empty()) {
        room->player1->client = c;
        room->player1->name   = name;
        room->player1->uuid   = uuidm;
    } else if (room->player2->uuid.empty()) {
        room->player2->client = c;
        room->player2->name   = name;
        room->player2->uuid   = uuidm;
    } else if (room->player1->uuid == uuidm) {
        room->player1->client = c;
        room->player1->name   = name;
        room->player1->uuid   = uuidm;
    } else if (room->player2->uuid == uuidm) {
        room->player2->client = c;
        room->player2->name   = name;
        room->player2->uuid   = uuidm;
    } else {
        return false;
    }

    return true;
};

// 加入房间（观众）
bool Manager::room_subscrib(cinatra::coro_http_connection* c, std::string& id, std::string& name, std::string& uuidm) {
    std::shared_ptr<Room> room;
    {
        std::lock_guard<std::mutex> lock(this->mu);
        auto                        it = rooms.find(id);
        if (it == rooms.end()) return false;
        room = it->second;
    }

    if (!room) return false; // null

    std::lock_guard<std::mutex> lock(room->mu);
    if (room->subscriber.size() >= 10) return false; // max 10

    auto it = room->subscriber.find(uuidm);
    if (it != room->subscriber.end()) {
        it->second->client = c;
        it->second->name   = name;
        it->second->uuid   = uuidm;
        return true;
    }

    auto player    = std::make_shared<Player>();
    player->client = c;
    player->name   = name;
    player->uuid   = uuidm;
    room->subscriber.emplace(uuidm, player);
    return true;
};


// 消息转发（玩家互相）
cinatra::coro_http_connection* Manager::room_pl2pl(std::string& id, std::string& uuidm) {
    std::shared_ptr<Room> room;
    {
        std::lock_guard<std::mutex> lock(this->mu);
        auto                        it = rooms.find(id);
        if (it == rooms.end()) return nullptr;
        room = it->second;
    }

    if (!room) return nullptr; // null

    std::lock_guard<std::mutex> lock(room->mu);
    if (room->player1->uuid == uuidm) return room->player2->client;
    else if (room->player2->uuid == uuidm) return room->player1->client;
    return nullptr;
};

// 消息转发（玩家转观众）
cinatra::coro_http_connection* Manager::room_pl2se(std::string& id, std::string& uuidm, std::string& uuidf) {
    std::shared_ptr<Room> room;
    {
        std::lock_guard<std::mutex> lock(this->mu);
        auto                        it = rooms.find(id);
        if (it == rooms.end()) return nullptr;
        room = it->second;
    }

    if (!room) return nullptr; // null

    std::lock_guard<std::mutex> lock(room->mu);
    if (room->player1->uuid != uuidm && room->player2->uuid != uuidm) return nullptr;

    auto it = room->subscriber.find(uuidf);
    if (it != room->subscriber.end()) return it->second->client;
    return nullptr;
};

// 消息转发（观众转玩家）
cinatra::coro_http_connection* Manager::room_se2pl(std::string& id, std::string& uuidm, std::string& uuidf) {
    std::shared_ptr<Room> room;
    {
        std::lock_guard<std::mutex> lock(this->mu);
        auto                        it = rooms.find(id);
        if (it == rooms.end()) return nullptr;
        room = it->second;
    }

    if (!room) return nullptr; // null

    std::lock_guard<std::mutex> lock(room->mu);
    if (room->subscriber.find(uuidm) == room->subscriber.end()) return nullptr;

    if (room->player1->uuid == uuidf) return room->player1->client;
    else if (room->player2->uuid == uuidf) return room->player2->client;
    return nullptr;
};