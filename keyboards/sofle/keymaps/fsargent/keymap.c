 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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
// #include "g/keymap_combo.h"
#include "oled.c"
#include "encoder.c"
#include "rgb.c"

enum layers { BASE, WIN, NAV, NUM, SYM, GAME  };
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    // TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    LAYR // Our custom tap dance key; add any other tap dance keys to this enum
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


//Default keymap. This can be changed in Via. Use oled.c and encoder.c to change beavior that Via cannot change.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \    s   \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

  [BASE] = LAYOUT(
    KC_GRV,             KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,             KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    MT(MOD_MEH,KC_ESC), KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,            KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, G(KC_ENT),                  KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
                        KC_LALT, KC_LCTL, MO(SYM), CMD_T(KC_BSPC), LT(NAV, KC_TAB),   LT(SYM, KC_ENT),  KC_SPC,  CTL_T(KC_ESC), KC_LBRC, KC_RBRC
  ),
  [WIN] = LAYOUT(
    _______,KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     _______,
    _______,KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     _______,
    _______,KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,  _______,
    _______,KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  MEH(KC_F13),     _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  _______,
                    KC_LGUI,   KC_LALT, MO(SYM), LCTL_T(KC_BSPC),  LT(NAV, KC_TAB),      _______,_______, _______, _______,TO(GAME)
  ),
  [NAV] = LAYOUT(
    C(KC_GRV),  KC_WH_L,       KC_WH_D,         KC_WH_U,        KC_WH_R,        G(KC_ENT),                     KC_VOLU,    KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_LCTL,
    C(KC_TAB),     LGUI(KC_LEFT), LGUI(KC_DOWN),   LGUI(KC_UP),    LGUI(KC_RGHT),  KC_ENT,                            KC_VOLD,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LALT,
    KC_LALT,    KC_LEFT,       KC_DOWN,         KC_UP,          KC_RGHT,        KC_SPC,                            KC_MS_BTN4, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_LGUI,
    KC_LSFT,    S(A(KC_LEFT)), LALT(KC_LEFT),   LALT(KC_RGHT),  S(A(KC_RGHT)), LALT(KC_BSPC), G(KC_ENT),      TO(3),  KC_MS_BTN5, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_LSFT,
                               _______,         _______,        _______,        _______,      _______,     KC_MS_BTN1,KC_MS_BTN2,KC_MS_BTN3, _______, TD(LAYR)
  ),

  [NUM] = LAYOUT(
    KC_ESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                     KC_F6,    KC_F7,    KC_F8,      KC_F9,      KC_F10,     KC_F11,
    KC_PSLS, KC_NO,    KC_P7,    KC_P8,    KC_P9,    KC_PPLS,                   KC_LCBR,  KC_RCBR,  KC_MINS,    KC_TILDE,   KC_SLSH,    KC_F12,
    KC_PAST, KC_PSCR,  KC_P4,    KC_P5,    KC_P6,    KC_PEQL,                   KC_LPRN,  KC_RPRN,  KC_EQL,     KC_MINS,    KC_PIPE,    KC_PSCR,
    KC_PMNS, KC_NLCK,  KC_P1,    KC_P2,    KC_P3,    KC_PENT, _______,  TO(5),  KC_LBRC,  KC_RBRC,  KC_PLUS,    KC_UNDS,    KC_BSLS,    KC_NLCK,
                       KC_RST,   KC_P0,    _______,  _______, _______,  _______,_______,  _______,  _______,  _______
  ),
  [SYM] = LAYOUT(
    KC_ESC,     KC_F1,    KC_F2,      KC_F3,  KC_F4,  KC_F5,                            KC_F6,    KC_F7,    KC_F8,  KC_F9,    KC_F10,    KC_F11,
    _______,    KC_SLSH,  KC_GRV,     KC_MINS,KC_LCBR,KC_RCBR,                          KC_PSLS,  KC_P7,    KC_P8,  KC_P9,    KC_PPLS,   KC_F12,
_______,    KC_PIPE,  KC_MINS,    KC_EQL, KC_LPRN,KC_RPRN,                              KC_PAST,  KC_P4,    KC_P5,  KC_P6,    KC_PEQL,   KC_PSCR,
    _______,    KC_BSLS,  KC_UNDS,    KC_PLUS,KC_LBRC,KC_RBRC, C(G(KC_SPC)),   TO(0),   KC_PMNS,  KC_P1,    KC_P2,  KC_P3,    KC_PENT,   KC_NLCK,
                KC_RST,     _______,_______,_______,_______,                   _______, _______,  _______,  KC_0,   KC_DOT
  ),
   [GAME] = LAYOUT(
    KC_ESC,    KC_ESC,     KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_BSPC,
    KC_TAB,    KC_TAB,     KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    MEH(KC_NO),MEH(KC_NO), KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    EEP_RST,
    KC_LSFT,   KC_LSFT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  MEH(KC_F13),     TO(2),KC_N,    KC_M,    KC_COMM, CMB_TOG,  CMB_TOG,
                           MO(SYM), KC_LALT, MEH(KC_NO),KC_LCTRL, KC_SPC,             _______,    _______, _______, KC_ASTG,TO(BASE)
  ),
};




// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        // if (!state->pressed) return TD_SINGLE_TAP;
        // else

         return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;

        // case TD_SINGLE_TAP:
        //      // Check to see if the layer is already set
        //     if (layer_state_is(SYM)) {
        //         // If already set, then switch it off
        //         layer_off(SYM);
        //     } else {
        //         // If not already set, then switch the layer on
        //         layer_on(SYM);
        //     }
        //     break;
        case TD_SINGLE_HOLD:
            layer_on(SYM);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(WIN)) {
                // If already set, then switch it off
                layer_off(WIN);
            } else {
                // If not already set, then switch the layer on
                layer_on(WIN);
            }
            break;
        case TD_DOUBLE_HOLD:
            layer_on(NUM);
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(SYM);
    }
     if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(NUM);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 200)
};
