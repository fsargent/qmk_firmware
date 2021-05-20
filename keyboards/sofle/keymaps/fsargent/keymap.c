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
#include "oled.c"
#include "encoder.c"

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_COLN);
    } else {
        register_code(KC_SCLN);
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_COLN);
    } else {
        unregister_code(KC_SCLN);
    }
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
};

enum layers { BASE, MBO, MEDR, NAVR, MOUR, NSSL, NSL, FUNL, GAME};

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
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[BASE] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  LT(NSL, KC_TAB),   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_EQL,
  KC_LCTRL,  KC_A,  KC_S, KC_D, KC_F, KC_G,                                      KC_H, KC_J, KC_K, KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  MT(MOD_MEH,KC_Z),   KC_X,    KC_C,    KC_V,    KC_B, S(G(KC_A)),               KC_MEDIA_PLAY_PAUSE,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_LSFT,
  TG(NSL),KC_LALT, LT(NSSL, KC_DEL),  MT(MOD_LGUI,KC_BSPC),  LT(NAVR, KC_TAB),       LT(MEDR, KC_ENT),  LT(NSL, KC_SPC),  LT(FUNL,KC_ESC ),  KC_RALT, TG(GAME)
),
/*
 * GAMING
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[GAME] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_NO,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,  KC_SCLN,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     KC_MEDIA_PLAY_PAUSE,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                KC_NO,KC_LALT,KC_LCTRL, KC_SPC, KC_LCTRL,            KC_ENT,  KC_SPC, KC_ENT, KC_RGUI, TG(GAME)
),


  [NAVR] = LAYOUT(
   KC_HOME, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP),LGUI(KC_RGHT), LGUI(KC_BSPC),                           _______,  _______  , _______,  _______ ,  _______ ,_______,
   KC_PGUP, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), KC_ENT,                                                KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,_______ ,
   KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,KC_RGHT, KC_SPC,                                             KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,_______ ,
   KC_LSFT, LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP),LALT(KC_RGHT),  LALT(KC_BSPC),KC_ENT,                 _______,    SCMD(KC_Z),  LCMD(KC_V),  LCMD(KC_C), LCMD(KC_X),LCMD(KC_Z),_______ ,
   KC_NP,   KC_NP,   KC_NA,   KC_NA,   KC_NA,                                                        KC_ENT,  KC_BSPC, KC_DEL,  KC_NP,   KC_NP
  ),

  [MBO] = LAYOUT(
    KC_ESC, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,

  _______ , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,_______ ,
    _______ ,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,_______ ,
    _______ ,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,_______,  _______,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,_______ ,
    KC_NP,   KC_NP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_NP,   KC_NP
  ),
  [MEDR] = LAYOUT(
    KC_ESC, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
   _______ , KC_RST,  KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_TOG,  KC_MOD,  KC_HUI,  KC_SAI,  KC_VAI,_______ ,
   _______ , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NA,   KC_NU,   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,_______ ,
   _______ , KC_NA,   KC_ALGR, KC_NA,   KC_NA,   KC_NA,  _______,  _______,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,_______ ,
   KC_NP,   KC_NP,   KC_NA,   KC_NA,   KC_NA,   KC_MSTP, KC_MPLY, KC_MUTE, KC_NP,   KC_NP
  ),

  [FUNL] = LAYOUT(
    KC_ESC, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,

  _______ ,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_RST,_______ ,
  _______ ,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, KC_NA,   KC_LSFT, KC_LGUI, KC_LALT,KC_LCTL,_______ ,
  _______ ,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,_______,  _______,   KC_NA,   KC_NA,   KC_NA,   KC_ALGR, KC_NA,_______ ,
    KC_NP,   KC_NP,   KC_APP,  KC_SPC,  KC_TAB,  KC_NA,   KC_NA,   KC_NA,   KC_NP,   KC_NP
  ),
  [NSL] = LAYOUT(
    KC_ESC, _______ , KC_SPC , KC_PSLS , KC_PAST , KC_PMNS,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
    _______ ,KC_NA,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,           KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_RST,_______,
    _______ ,KC_NA,  KC_P4,    KC_P5,    KC_P6,    KC_PEQL,             KC_NA,   KC_LSFT, KC_LGUI, KC_LALT,KC_LCTL,_______,
    _______ ,KC_NA,  KC_P1,    KC_P2,    KC_P3,    KC_PENT, _______,           _______,  KC_NA,   KC_NA,   KC_COMM,  KC_DOT,  KC_NA,_______,
    TG(NSL),KC_MEH, LT(NSSL, KC_PDOT),  KC_BSPC,  LT(NAVR, KC_P0),       LT(MEDR, KC_ENT),  LT(NSL, KC_SPC),  LT(FUNL,KC_ESC ),  KC_RALT, TG(GAME)

  ),
  [NSSL] = LAYOUT(
KC_EQL	, KC_PIPE, 	 KC_BSLS,    	_______, 	 KC_LT, 	 KC_GT,				 _______,	 _______, 	 _______,	 _______, 	 _______, 	_______,
KC_MINS, 	 KC_AMPR, 	 KC_ASTR,	 KC_LPRN,	 KC_LCBR,	 KC_RCBR,				 KC_NA,	 KC_NA,	 KC_NA,	 KC_NA,	 KC_RST,	_______,
KC_ASTR,	 KC_DLR,    	 KC_PERC,	 KC_CIRC,   	 KC_LPRN,	 KC_RPRN,				 KC_NA,	 KC_LSFT,	 KC_LGUI,	 KC_LALT,	KC_LCTL,	 _______,
KC_PLUS, 	 KC_EXLM,	 KC_AT,	 KC_HASH,	 KC_LBRC,	 KC_RBRC,	_______,    		 _______,	 KC_NA,	 KC_NA,	 KC_NA, 	 KC_ALGR,  	 KC_NA,	_______,
	KC_NP,	 KC_LPRN,	 KC_RPRN,	 KC_UNDS,				 KC_NP,	 KC_NA,	 KC_NA,	 KC_NA,	 KC_NP,	 KC_NP
  ),[MOUR] = LAYOUT(
    KC_ESC, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
    _______ , KC_RST,  KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,_______ ,
    _______ , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NA,   KC_NU,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,_______ ,
    _______ , KC_NA,   KC_ALGR, KC_NA,   KC_NA,   KC_NA,  _______,  _______,   KC_NU,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,_______ ,
    KC_NP,   KC_NP,   KC_NA,   KC_NA,   KC_NA,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NP,   KC_NP
  )

};
