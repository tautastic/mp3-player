#pragma once

#include <array>

namespace core {

enum class Button {
    Up,
    Right,
    Down,
    Left,
};

inline constexpr std::array all_buttons{Button::Up, Button::Right, Button::Down, Button::Left};

}
