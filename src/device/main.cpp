#include <Arduino.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "core/button.hpp"
#include "core/debouncer.hpp"
#include "core/protocol.hpp"

namespace {

struct Pin {
    std::uint8_t number;
    core::Button button;
};

constexpr std::array pins{
    Pin{5, core::Button::Up},
    Pin{6, core::Button::Right},
    Pin{20, core::Button::Down},
    Pin{21, core::Button::Left},
};

std::array<core::Debouncer, pins.size()> debouncers;

void send(core::Button button)
{
    const std::string_view line = core::to_line(button);
    Serial.write(line.data(), line.size());
}

}

void setup()
{
    Serial.begin(115200);
    for (const Pin& pin : pins) {
        pinMode(pin.number, INPUT_PULLUP);
    }
}

void loop()
{
    for (std::size_t i = 0; i < pins.size(); ++i) {
        const bool down = digitalRead(pins[i].number) == LOW;
        if (debouncers[i].was_pressed(down, millis())) {
            send(pins[i].button);
            return;
        }
    }
}