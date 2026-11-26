#pragma once

#include <queue>

#include <lvgl.h>

#include "core/button.hpp"

namespace ui {

class Keypad {
public:
    explicit Keypad(lv_group_t* group);
    ~Keypad();

    Keypad(const Keypad&) = delete;
    Keypad& operator=(const Keypad&) = delete;

    void press(core::Button button);

private:
    static void read(lv_indev_t* indev, lv_indev_data_t* data);

    lv_indev_t* indev_;
    std::queue<lv_key_t> keys_;
    bool pressed_ = false;
};

}