#pragma once

#include <cstdint>

namespace core {

class Debouncer {
public:
    static constexpr std::uint32_t delay_ms = 30;

    [[nodiscard]] constexpr bool was_pressed(bool down, std::uint32_t now_ms)
    {
        if (down != last_reading_) {
            last_reading_ = down;
            last_change_ms_ = now_ms;
        }
        if (now_ms - last_change_ms_ >= delay_ms && down != stable_) {
            stable_ = down;
            return down;
        }
        return false;
    }

private:
    bool stable_ = false;
    bool last_reading_ = false;
    std::uint32_t last_change_ms_ = 0;
};

}
