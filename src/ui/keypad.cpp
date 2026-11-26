#include "ui/keypad.hpp"

#include <optional>
#include <utility>

namespace ui {
namespace {

std::optional<lv_key_t> to_key(core::Button button)
{
    switch (button) {
    case core::Button::Up:
        return LV_KEY_UP;
    case core::Button::Down:
        return LV_KEY_DOWN;
    case core::Button::Right:
    case core::Button::Left:
        return std::nullopt;
    }
    std::unreachable();
}

}

Keypad::Keypad(lv_group_t* group)
    : indev_{lv_indev_create()}
{
    lv_indev_set_type(indev_, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_, read);
    lv_indev_set_user_data(indev_, this);
    lv_indev_set_group(indev_, group);
}

Keypad::~Keypad()
{
    lv_indev_delete(indev_);
}

void Keypad::press(core::Button button)
{
    if (const std::optional<lv_key_t> key = to_key(button)) {
        keys_.push(*key);
    }
}

void Keypad::read(lv_indev_t* indev, lv_indev_data_t* data)
{
    Keypad& self = *static_cast<Keypad*>(lv_indev_get_user_data(indev));
    if (self.pressed_) {
        self.pressed_ = false;
        data->state = LV_INDEV_STATE_RELEASED;
    }
    else if (!self.keys_.empty()) {
        self.pressed_ = true;
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = self.keys_.front();
        self.keys_.pop();
    }
    data->continue_reading = self.pressed_ || !self.keys_.empty();
}

}