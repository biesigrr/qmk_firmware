#include QMK_KEYBOARD_H
#include <stdint.h>

#define GAME_MODE_LAYER 4

void housekeeping_task_user(void) {
    if (!is_transport_connected()) {
        if (IS_LAYER_OFF(GAME_MODE_LAYER)) {
            layer_on(GAME_MODE_LAYER);
        }
    } else {
        if (IS_LAYER_ON(GAME_MODE_LAYER)) {
            layer_off(GAME_MODE_LAYER);
        }
    }
}