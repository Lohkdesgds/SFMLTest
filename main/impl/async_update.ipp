#pragma once

#include "async_update.h"

template <typename Func, typename... Args>
inline AsyncUpdate::AsyncUpdate(std::chrono::milliseconds interval, Func&& func, Args&&... args) {
    m_update_interval = interval;
    
    m_thread = std::thread([this, func = std::forward<Func>(func), args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
        m_running = true;
        while(m_running) {
            auto now = std::chrono::system_clock::now();
            if (now - m_last_call >= m_update_interval) {
                m_last_call = now;
                std::apply(func, std::move(args));
            }

            std::this_thread::yield(); // Yield to allow other threads to run

            const auto sleep_duration = m_update_interval - (std::chrono::system_clock::now() - m_last_call);
            if (sleep_duration > std::chrono::milliseconds(0)) {
                std::this_thread::sleep_for(sleep_duration);
            }
        }
    });
}