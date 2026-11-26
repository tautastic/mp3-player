#include <lvgl.h>

#include <cstdint>
#include <cstdio>
#include <optional>
#include <print>
#include <string>
#include <utility>

#include "core/protocol.hpp"
#include "simulator/serial_port.hpp"
#include "ui/keypad.hpp"
#include "ui/menu.hpp"

namespace {

constexpr std::int32_t screen_width = 240;
constexpr std::int32_t screen_height = 280;
constexpr const char* default_port = "/dev/ttyACM0";

std::optional<simulator::SerialPort> open_port(const char* path)
{
    auto port = simulator::SerialPort::open(path);
    if (!port) {
        std::println(stderr, "{}: {}, using the keyboard only", path, port.error().message());
        return std::nullopt;
    }
    return std::move(*port);
}

void forward_lines(std::optional<simulator::SerialPort>& port, const char* path, ui::Keypad& keypad)
{
    if (!port) {
        return;
    }
    const auto lines = port->read_lines();
    if (!lines) {
        std::println(stderr, "{}: connection lost", path);
        port.reset();
        return;
    }
    for (const std::string& line : *lines) {
        if (const auto button = core::parse_line(line)) {
            keypad.press(*button);
        }
    }
}

}

int main(int argc, char* argv[])
{
    const char* path = argc > 1 ? argv[1] : default_port;
    std::optional<simulator::SerialPort> port = open_port(path);

    lv_init();
    lv_sdl_window_create(screen_width, screen_height);
    lv_group_t* group = lv_group_create();
    lv_indev_set_group(lv_sdl_keyboard_create(), group);
    ui::Keypad keypad{group};
    ui::create_menu(lv_screen_active(), group);

    while (true) {
        forward_lines(port, path, keypad);
        lv_timer_handler();
        lv_delay_ms(5);
    }
}