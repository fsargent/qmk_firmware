/* Copyright 2021 Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
<<<<<<< HEAD
#include "action_layer.h"

enum layer_names {
  _BASE,
  _FUNC,
  _EXT1,
  _EXT2
};

bool numlock_set = false;

enum custom_keycodes {
    PROG = SAFE_RANGE,
};

enum td_keycodes {
    TD_ENTER_LAYER
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for KP_ENTER, twice for _FUNC layer
    [TD_ENTER_LAYER] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_KP_ENTER, 1),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Base layer (numpad)
  [_BASE] = LAYOUT(
           KC_PSLS,  KC_KP_ASTERISK, KC_KP_MINUS, 
  KC_KP_7, KC_KP_8,  KC_KP_9,        KC_KP_PLUS, 
  KC_KP_4, KC_KP_5,  KC_KP_6,        KC_NO, 
  KC_KP_1, KC_KP_2,  KC_KP_3,        KC_PENT, 
  KC_KP_0, KC_KP_0,  KC_KP_DOT,      KC_NO 
  ),
  // Function layer (numpad)
  [_FUNC] = LAYOUT(
           KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO
  ),
  [_EXT1] = LAYOUT(
           KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO
  ),
  [_EXT2] = LAYOUT(
           KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_logo(void) {
  static const char PROGMEM tidbit_oled[] = {
    0x00, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 
    0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3e, 0x3e, 0x7e, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
    0x1f, 0x1f, 0x3f, 0x7e, 0xfe, 0xfe, 0xfc, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xfe, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
    0xe0, 0xf0, 0xf0, 0xf8, 0xff, 0xff, 0xbf, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x03, 
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x07, 0x07, 0xbf, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x3f, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 
    0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 
    0xf8, 0xf8, 0xf8, 0x7c, 0x7c, 0x7c, 0x7e, 0x3e, 0x3f, 0x3f, 0x1f, 0x0f, 0x07, 0x01, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
    0xf8, 0x7c, 0x7c, 0x7c, 0x7e, 0x3f, 0x3f, 0x1f, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x7f, 0xff, 0xff, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  
  oled_write_raw_P(tidbit_oled, sizeof(tidbit_oled));
};


void oled_task_user(void) { render_logo(); }
#endif

void matrix_init_user(void) { matrix_init_remote_kb(); }

void matrix_scan_user(void) { matrix_scan_remote_kb(); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_remote_kb(keycode, record);

    // Get the current NLCK status & set if not set.
    // Only do this once, in case user has a NLCK key
    // and wants to disable it later on.
    if (!numlock_set && record->event.pressed) {
        led_t led_state = host_keyboard_led_state();
        if (!led_state.num_lock) {
            register_code(KC_NLCK);
        }
        numlock_set = true;
    }

    switch (keycode) {
        case PROG:
            if (record->event.pressed) {
                set_bitc_LED(LED_DIM);
                rgblight_disable_noeeprom();
                oled_off();
                bootloader_jump();  // jump to bootloader
            }
            break;

        default:
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_NUM_LOCK))
        set_bitc_LED(LED_DIM);
    else
        set_bitc_LED(LED_OFF);
}
=======

enum layers {
    _BASE = 0,
    _VIA1,
    _VIA2,
    _VIA3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
                            KC_PSLS, KC_PAST, KC_PMNS, 
    KC_VOLD, KC_VOLU, KC_P7, KC_P8,   KC_P9,   KC_PPLS, 
    KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PPLS, 
    KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   KC_PENT, 
    KC_TRNS, KC_TRNS, KC_P0, KC_P0,   KC_PDOT, KC_PENT  
    ),

    [_VIA1] = LAYOUT(
                    ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___  
    ),

    [_VIA2] = LAYOUT(
                    ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___
    ),

    [_VIA3] = LAYOUT(
                    ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___
    ),
};
>>>>>>> origin/master
