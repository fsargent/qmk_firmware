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
#include "rgb.c"

enum layers { BASE, NAV, SYM, GAME};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
		KC_GRV,				KC_1,	KC_2,	KC_3,	KC_4,	KC_5,										KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_MINS,
		LT(SYM,KC_TAB),		KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,										KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,	KC_EQL,
		MT(MOD_MEH,KC_ESC),	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,										KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,KC_QUOT,
		MT(MOD_LSFT,KC_DEL),KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	G(KC_ENT),				CG_TOGG,	KC_N,	KC_M,	KC_COMM,KC_DOT,	KC_SLSH,KC_LSFT,
		MT(MOD_LCTL,KC_LBRC),MT(MOD_LALT,KC_RBRC),TO(BASE),CMD_T(KC_BSPC),TT(NAV),			KC_ENT,		KC_SPC,	TT(SYM),KC_LBRC,KC_RBRC
	),
	[NAV]=LAYOUT(
		C(KC_GRV),	MEH(2),		C(KC_F2),	KC_WH_U,	KC_WH_R,G(KC_ENT),								KC_VOLU,			KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MUTE,	KC_LCTL,
		KC_TAB,		A(KC_BSPC),	KC_PGUP,	KC_UP,		KC_ENT,	A(KC_DEL),								KC_VOLD,			KC_HOME,	KC_PGDN,	KC_PGUP,	KC_END,		KC_LALT,
		C(KC_TAB),	A(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,A(KC_RGHT),								RGB_MODE_FORWARD,	KC_MS_L,	KC_MS_D,	KC_MS_U,	KC_MS_R,	KC_LGUI,
		KC_LSFT,	KC_HOME,	KC_PGDN,	KC_SPC,		KC_SPC,	KC_END,		G(KC_ENT),		TG(GAME),	KC_MS_BTN5,			KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_WH_R,	KC_LSFT,
								MT(MOD_LCTL,KC_COMM),	MT(MOD_LALT,KC_DOT),_______,_______,_______,	KC_MS_BTN1,			KC_MS_BTN2,	KC_MS_BTN3,	KC_LPRN,	KC_RPRN
	),
	[SYM]	=	LAYOUT(
		C(G(KC_SPC)),	KC_F1,	KC_F2,	KC_F3,		KC_F4,		KC_F5,									KC_F6,		KC_F7,	KC_F8,		KC_F9,	KC_F10,	KC_F11,
		_______,		KC_NO,	KC_NO,	KC_NO,		KC_LCBR,	KC_RCBR,								KC_RCBR,	KC_P7,	KC_P8,		KC_P9,	KC_DOT,	KC_F12,
		_______,		KC_NO,	KC_NO,	KC_NO,		KC_LPRN,	KC_RPRN,								KC_RPRN,	KC_P4,	KC_P5,		KC_P6,	KC_0,	KC_PSCR,
		_______,		KC_NO,	KC_NO,	KC_NO,		KC_LBRC,	KC_RBRC,	C(G(KC_SPC)),		KC_NO,	KC_RBRC,	KC_P1,	KC_P2,		KC_P3,	KC_BSLS,KC_NLCK,
										_______,_______,_______,_______,_______,				_______,	_______,		KC_NO,		KC_0,	KC_DOT
	),
	 [GAME] = LAYOUT(
		KC_ESC,		KC_ESC,	 	KC_1,	KC_2,	KC_3,	KC_4,								KC_5,	KC_6,	KC_7,	KC_8,	KC_9,	KC_0,
		KC_TAB,		KC_TAB,	 	KC_Q,	KC_W,	KC_E,	KC_R,								KC_T,	KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,
		MEH(KC_NO),	MEH(KC_NO),	KC_A,	KC_S,	KC_D,	KC_F,								KC_G,	KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,
		KC_LSFT,	KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,  MEH(KC_F13),		TG(GAME),	KC_B,	KC_N,	KC_M,	KC_COMM, KC_DOT,  KC_SLSH,
						 _______,	_______,MEH(KC_NO),  KC_LCTRL,KC_SPC,				_______,_______, _______, KC_ASTG,	TG(GAME)
	),
};

enum combo_events {
//   BSPC_SPC_DEL,
	LPAREN,
	RPAREN,
	PAREN,
//   BRACES,
//   CBRACES,
	CTRLC,
	CTRLR,
	CAL,
//   BSPC_LSFT_CLEAR,
	COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM asdf_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM zxcv_combo[] = {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM jklsemi_combo[] = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM cal_combo[] = {KC_C, KC_A, KC_L, COMBO_END};




combo_t key_combos[] = {
	[LPAREN] = COMBO_ACTION(zx_combo),
	[PAREN] = COMBO_ACTION(xc_combo),
	[RPAREN] = COMBO_ACTION(cv_combo),
	[CTRLC] = COMBO_ACTION(asdf_combo),

	[CTRLR] = COMBO_ACTION(qr_combo),
//   [BRACES] = COMBO_ACTION(brace_combo),
//   [CBRACES] = COMBO_ACTION(curly_combo),
//   [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
	[CAL] = COMBO_ACTION(cal_combo),

	// Lock computer combo!
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
	switch(combo_index) {

		case LPAREN:
			if (pressed) {
				SEND_STRING("(");
				tap_code16(A(KC_LEFT));
				tap_code16(KC_LEFT);
			}
			break;
		case RPAREN:
			if (pressed) {
				SEND_STRING(")");
			}
			break;
		case PAREN:
			if (pressed) {
				SEND_STRING("()");
				 tap_code16(KC_LEFT);
			}
			break;
		case CTRLC:
			if (pressed) {
				tap_code16(C(KC_C));
				}
			break;
		case CTRLR:
			if (pressed) {
				tap_code16(C(KC_R));
				}
			break;
		case CAL:
			if (pressed) {
				SEND_STRING("Would you like to find a time on my calendar that works for you? https://felixsargent.com/calendar.");
				}
			break;
		// case SWAP_HANDS2:
		//   if (pressed) {
		//	 tap_code16(SH_TG);
		//	 }
		//   break;
	}
}


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//	 case LOWER:
//	   if (record->event.pressed) {
//		 layer_on(_LOWER);
//		 update_tri_layer(_LOWER, _RAISE, _ADJUST);
//	   } else {
//		 layer_off(_LOWER);
//		 update_tri_layer(_LOWER, _RAISE, _ADJUST);
//	   }
//	   return false;
//	 case RAISE:
//	   if (record->event.pressed) {
//		 layer_on(_RAISE);
//		 update_tri_layer(_LOWER, _RAISE, _ADJUST);
//	   } else {
//		 layer_off(_RAISE);
//		 update_tri_layer(_LOWER, _RAISE, _ADJUST);
//	   }
//	   return false;
//	 }
//   return true;
// }



uint32_t layer_state_set_user(uint32_t state) {

		rgblight_set_layer_state(2, layer_state_cmp(state, 2));
		rgblight_set_layer_state(3, layer_state_cmp(state, 1));
		rgblight_set_layer_state(4, layer_state_cmp(state, 5));
		rgblight_set_layer_state(5, layer_state_cmp(state, 4));
		rgblight_set_layer_state(6, layer_state_cmp(state, 3));
		return state;
		switch (biton32(state)) {
			case GAME:
					autoshift_disable();
					break;
			default:
					autoshift_enable();
					break;
			}
	return state;
}


