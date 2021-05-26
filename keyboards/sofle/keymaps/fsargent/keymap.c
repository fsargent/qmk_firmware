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

enum layers { BASE, GAME, NAV, FN, NUM, SYM  };
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    QUOT_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum
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
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[BASE] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_EQL,
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H, KC_J, KC_K, KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT, MT(MOD_MEH,KC_Z),   KC_X,    KC_C,    KC_V,    KC_B, S(G(KC_A)),               TO(1),KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_LSFT,
  KC_DEL, KC_LALT,  TD(QUOT_LAYR),  MT(MOD_LGUI,KC_BSPC),  LT(NAV, KC_TAB),               LT(SYM, KC_ENT),  LT(NUM, KC_SPC),  LT(FN,KC_ESC),  TO(NAV), TO(GAME)
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
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,         TO(2),KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ASTG,
        TD(QUOT_LAYR),LT(FN,KC_LALT),KC_LCTRL, KC_LCTRL, KC_SPC,           KC_BSPC,  KC_SPC, KC_ENT, KC_RGUI, TO(BASE)
),


  [NAV] = LAYOUT(
   KC_HOME, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, LGUI(KC_BSPC),                                                  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_MUTE,
   KC_PGUP, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP),LGUI(KC_RGHT), KC_ENT,                                      KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______ ,
   KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,KC_RGHT, KC_SPC,                                                           KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______ ,
   KC_LSFT, S(A(KC_LEFT)), LALT(KC_LEFT),LALT(KC_RGHT), S(A(KC_RGHT)), LALT(KC_BSPC),KC_ENT,        TO(3),  SCMD(KC_Z), KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______ ,
          KC_RST,    _______,   _______, _______,  _______,                                       KC_BTN1,KC_BTN2, KC_DEL,  KC_NP,   TO(BASE)
  ),


  [FN] = LAYOUT(
    KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______ ,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                      KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, KC_F12,
    _______ ,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK,                      KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, RGB_MOD,
    _______ ,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,   _______,  TO(4),   KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, RGB_M_P ,
     KC_RST,   KC_NP,    _______, _______,  _______,                             KC_NA,   KC_NA,   KC_NA,   KC_NP,   TO(BASE)
  ),
  [NUM] = LAYOUT(
    KC_ESC,  KC_NLCK , KC_SPC , KC_PSLS , KC_PAST , KC_PMNS,                            KC_NLCK, KC_SPC,  KC_PSLS,  KC_PAST, KC_PMNS,_______,
    _______, KC_NA,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,                             KC_NA,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,_______,
    _______, KC_NA,  KC_P4,    KC_P5,    KC_P6,    KC_PEQL,                             KC_NA,  KC_P4,    KC_P5,    KC_P6,    KC_PEQL,_______,
    MO(FN) ,KC_MEH,  KC_P1,    KC_P2,    KC_P3,    KC_PENT, _______,           TO(5),  KC_MEH,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,_______,
       KC_RST, LT(SYM, KC_P0),   _______, _______,  _______,       LT(SYM, KC_ENT),  LT(NUM, KC_SPC),  LT(FN,KC_ESC ),  KC_RALT,TO(BASE)

  ),
  [SYM] = LAYOUT(
    KC_LT,      KC_GT,      KC_SLSH,    KC_PIPE,    KC_BSLS,     KC_EQL,                            KC_SLSH,    KC_PIPE,    KC_BSLS,     KC_EQL,  KC_LT,      KC_GT,
    KC_LCBR,    KC_RCBR,    KC_AMPR,    KC_ASTR,	KC_LPRN,     KC_MINS,                           KC_AMPR,    KC_ASTR,	KC_LPRN,     KC_MINS, KC_LCBR,    KC_RCBR,
    KC_LPRN,    KC_RPRN,    KC_DLR,     KC_PERC,    KC_CIRC,     KC_ASTR,                           KC_DLR,     KC_PERC,    KC_CIRC,     KC_ASTR, KC_LPRN,    KC_RPRN,
    KC_LBRC,    KC_RBRC,    KC_EXLM,    KC_AT,      KC_HASH,     KC_PLUS,   _______,    TO(0),      KC_EXLM,    KC_AT,      KC_HASH,     KC_PLUS, KC_LBRC,    KC_RBRC,
	   	   KC_RST,   KC_RPRN, _______, _______,  _______,  		                            	 KC_NA,	 KC_NA,	 KC_NA,     KC_NP,      TO(BASE)
  )
//   ,[MOU] = LAYOUT(
//     KC_RST, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
//     _______ , KC_NA,  KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,_______ ,
//     _______ , KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NA,   KC_NU,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,_______ ,
//     _______ ,  KC_NU,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,  _______,  TO(0),   KC_NU,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,_______ ,
//        KC_RST,   KC_NP,   _______,   KC_BTN1,   KC_BTN2,   KC_BTN1, KC_BTN3, KC_BTN2, TG(MOU),   TO(BASE)
//   )

//   [MED] = LAYOUT(
//     KC_ESC, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
//    _______ , KC_RST,  KC_NA,   KC_NA,   KC_NA,   KC_VOLU,   KC_TOG,  KC_MOD,  KC_HUI,  KC_SAI,  KC_VAI,_______ ,
//    _______ , KC_LGUI, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD,   KC_NU,   KC_MPRV, KC_VOLD, KC_MNXT, KC_MNXT,_______ ,
//    _______ , KC_NA,   KC_ALGR, KC_NA,   KC_NA,   KC_MUTE,  _______,  TO(4),   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,_______ ,
//    KC_RST,   KC_NP,    _______, _______,  _______,   KC_MSTP, KC_MPLY, KC_MUTE, KC_NP,   TO(BASE)
//   ),
};




// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 8, HSV_RED},     // Light 4 LEDs, starting with LED 6
    {37, 8, HSV_RED}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 6, HSV_PURPLE},
    {45, 6, HSV_PURPLE}
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 6, HSV_BLUE},
    {45, 6, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 6,  HSV_GOLDENROD},
    {45, 6, HSV_GOLDENROD}
);
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 6, HSV_TURQUOISE},
    {45, 6, HSV_TURQUOISE}
);
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 6, HSV_PINK},
    {45, 6, HSV_PINK}
);
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, NAV));
    rgblight_set_layer_state(4, layer_state_cmp(state, SYM));
    rgblight_set_layer_state(5, layer_state_cmp(state, NUM));
    rgblight_set_layer_state(6, layer_state_cmp(state, FN));
    rgblight_set_layer_state(3, layer_state_cmp(state, GAME));
    return state;
}
// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}




// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        return TD_TRIPLE_TAP;
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

        case TD_SINGLE_TAP:
             // Check to see if the layer is already set
            if (layer_state_is(NUM)) {
                // If already set, then switch it off
                layer_off(NUM);
            } else {
                // If not already set, then switch the layer on
                layer_on(NUM);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(SYM);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(NAV)) {
                // If already set, then switch it off
                layer_off(NAV);
            } else {
                // If not already set, then switch the layer on
                layer_on(NAV);
            }
            break;
        case TD_TRIPLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(FN)) {
                // If already set, then switch it off
                layer_off(FN);
            } else {
                // If not already set, then switch the layer on
                layer_on(FN);
            }
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(SYM);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};
