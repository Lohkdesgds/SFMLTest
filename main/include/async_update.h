#pragma once

#include <thread>
#include <chrono>

class AsyncUpdate {
private:
    std::thread m_thread;
    std::chrono::system_clock::time_point m_last_call;
    std::chrono::milliseconds m_update_interval = std::chrono::milliseconds(100);
    bool m_running = false;

    // Disable copy constructor and assignment operator
    AsyncUpdate(const AsyncUpdate&) = delete;
    AsyncUpdate& operator=(const AsyncUpdate&) = delete;

    // Disable move constructor and assignment operator
    AsyncUpdate(AsyncUpdate&&) = delete;
    AsyncUpdate& operator=(AsyncUpdate&&) = delete;
public:
    template <typename Func, typename... Args>
    AsyncUpdate(std::chrono::milliseconds interval, Func&& func, Args&&... args);

    ~AsyncUpdate();

    void join();
};

#include "async_update.ipp"