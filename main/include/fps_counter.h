#pragma once

#include <math.h>
#include <chrono>

class FPSCounter {
    static constexpr double fps_smooth_factor = 0.02;
    static constexpr double fps_max_diff_factor_reset = 0.8;

    double m_avg_fps = 0.0;
    std::chrono::high_resolution_clock::time_point m_last_time;
public:
    FPSCounter() = default;

    void tick();
    double get_fps() const;
};