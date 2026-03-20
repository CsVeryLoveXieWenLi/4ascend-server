/***
 * @Author: CsVeryLoveXieWenLi
 * @Description: 锁
 * @@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once

#include <atomic>
#include <thread>


class Spin {
public:
    Spin() = default;

    Spin(const Spin&)            = delete;
    Spin& operator=(const Spin&) = delete;

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) std::this_thread::yield();
    };

    void unlock() { flag.clear(std::memory_order_release); };

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};