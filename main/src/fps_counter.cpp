#include "fps_counter.h"


void FPSCounter::tick() {
    const auto now = std::chrono::high_resolution_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - m_last_time).count();

    m_last_time = now;

    if (elapsed > 0) {
        const auto instant_fps = 1000000.0 / elapsed;

        if (std::abs(instant_fps - m_avg_fps) > fps_max_diff_factor_reset * m_avg_fps) {
            m_avg_fps = instant_fps;
        }
        else {
            const auto smooth_adjusted = 50.0 * fps_smooth_factor / std::max(instant_fps, 1.0);
            m_avg_fps = (1.0 - smooth_adjusted) * m_avg_fps + smooth_adjusted * instant_fps;
        }

    }
    else {
        m_avg_fps = -1.0;
    }
}

double FPSCounter::get_fps() const {
    return m_avg_fps;
}