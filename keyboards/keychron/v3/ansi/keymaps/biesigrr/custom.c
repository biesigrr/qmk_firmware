#include QMK_KEYBOARD_H
#include <quantum/raw_hid.h>

#define CUSTOM_REPORT_LAYER_GET_REQ 0x34
#define CUSTOM_REPORT_LAYER_GET_ACK 0x35
#define CUSTOM_REPORT_LAYER_MOVE_REQ 0x36
#define CUSTOM_REPORT_LAYER_TOGGLE_REQ 0x37

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (data[0] == CUSTOM_REPORT_LAYER_GET_REQ) {
        uint8_t response[length];
        memset(response, 0, length);

        response[0] = CUSTOM_REPORT_LAYER_GET_ACK;
        response[1] = (layer_state >> 0) & 0xFF;
        response[2] = (layer_state >> 8) & 0xFF;
        response[3] = (layer_state >> 16) & 0xFF;
        response[4] = (layer_state >> 24) & 0xFF;

        raw_hid_send(response, length);
        return;
    }

    if (data[0] == CUSTOM_REPORT_LAYER_MOVE_REQ) {
        int8_t layer_number = data[1];

        layer_move(layer_number);

        // Just send back
        raw_hid_send(data, length);
        return;
    }

    if (data[0] == CUSTOM_REPORT_LAYER_TOGGLE_REQ) {
        int8_t layer_number = data[1];

        layer_invert(layer_number);

        // Just send back
        raw_hid_send(data, length);
        return;
    }
}