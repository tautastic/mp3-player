#pragma once

#include <optional>
#include <string_view>
#include <utility>

#include "core/button.hpp"

namespace core {

[[nodiscard]] constexpr std::string_view to_line(Button button)
{
    switch (button) {
    case Button::Up:
        return "UP\n";
    case Button::Right:
        return "RIGHT\n";
    case Button::Down:
        return "DOWN\n";
    case Button::Left:
        return "LEFT\n";
    }
    std::unreachable();
}

[[nodiscard]] constexpr std::string_view trim_line_end(std::string_view line)
{
    if (line.ends_with('\n')) {
        line.remove_suffix(1);
    }
    if (line.ends_with('\r')) {
        line.remove_suffix(1);
    }
    return line;
}

[[nodiscard]] constexpr std::optional<Button> parse_line(std::string_view line)
{
    for (const Button button : all_buttons) {
        if (trim_line_end(to_line(button)) == trim_line_end(line)) {
            return button;
        }
    }
    return std::nullopt;
}

}