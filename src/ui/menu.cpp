#include "ui/menu.hpp"

#include <array>

namespace ui {
namespace {

constexpr std::array titles{"Music", "Settings"};

void move_focus(lv_event_t* event)
{
    lv_group_t* group = lv_obj_get_group(lv_event_get_target_obj(event));
    switch (lv_event_get_key(event)) {
    case LV_KEY_UP:
        lv_group_focus_prev(group);
        break;
    case LV_KEY_DOWN:
        lv_group_focus_next(group);
        break;
    default:
        break;
    }
}

}

void create_menu(lv_obj_t* parent, lv_group_t* group)
{
    lv_obj_t* menu = lv_obj_create(parent);
    lv_obj_remove_style_all(menu);
    lv_obj_set_size(menu, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(menu, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(menu, 12, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(menu, 12, LV_STATE_DEFAULT);

    for (const char* title : titles) {
        lv_obj_t* item = lv_button_create(menu);
        lv_obj_set_width(item, lv_pct(100));
        lv_obj_set_style_bg_color(item, lv_palette_darken(LV_PALETTE_GREY, 3), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(item, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_FOCUSED);
        lv_obj_add_event_cb(item, move_focus, LV_EVENT_KEY, nullptr);
        lv_group_add_obj(group, item);

        lv_obj_t* label = lv_label_create(item);
        lv_label_set_text_static(label, title);
    }
}

}