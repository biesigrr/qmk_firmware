#include QMK_KEYBOARD_H

#define GAME_LAYER 1

bool chat_mode_toggled;
bool automatic_toggle;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (KC_ENTER == keycode && record->event.pressed) {
        if (IS_LAYER_ON(GAME_LAYER)) {
            chat_mode_toggled = true;
            automatic_toggle = true;
            layer_off(GAME_LAYER);
            return true;
        }
    }

    if ((KC_ESC == keycode || KC_ENTER == keycode) && record->event.pressed) {
        if (IS_LAYER_OFF(GAME_LAYER) && chat_mode_toggled) {
            chat_mode_toggled = false;
            automatic_toggle = true;
            layer_on(GAME_LAYER);
            return true;
        }
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    static bool game_mode_layer_on = false;
    if (game_mode_layer_on != IS_LAYER_ON_STATE(state, GAME_LAYER)) {
        if (!automatic_toggle) {
            chat_mode_toggled = false;
        }

        automatic_toggle = false;
        game_mode_layer_on = !game_mode_layer_on;
    }

    return state;
}