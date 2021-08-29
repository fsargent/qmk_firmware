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

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) { // This will do most of the grunt work with the keycodes.
	case ALT_TAB:
		if (record->event.pressed) {
			if (!is_alt_tab_active) {
			is_alt_tab_active = true;
			register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_TAB);
		} else {
			unregister_code(KC_TAB);
		}
		break;
	}
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
	if (timer_elapsed(alt_tab_timer) > 1000) {
	  unregister_code(KC_LALT);
	  is_alt_tab_active = false;
	}
  }
}

enum layers { BASE, CMK, WIN, GAME, SYM, NAV, WINNAV};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Tab size 4

	[BASE] = LAYOUT(
		KC_GRV,				KC_1,	KC_2,	KC_3,	KC_4,	KC_5,																KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
		LT(SYM,KC_TAB),		KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,																KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_EQL,
		MT(MOD_MEH,KC_ESC),	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,																KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,
		KC_LSFT,			KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	MAGIC_TOGGLE_CTL_GUI,							TO(CMK),	KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_DEL),
		MT(MOD_LCTL,KC_LBRC),	MT(MOD_LALT,KC_RBRC), LT(SYM,KC_DEL), MO(NAV), CMD_T(KC_BSPC), 					KC_SPC,		MT(MOD_LCTL, KC_ENT), 	MT(MOD_LALT,KC_DEL),	KC_MINS,	KC_EQL
	),
	[CMK] = LAYOUT(
		KC_GRV,				KC_1,	KC_2,	KC_3,	KC_4,	KC_5,					        									KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
		LT(SYM,KC_TAB),		KC_Q,	KC_W,	KC_F,	KC_P,	KC_B,																KC_J,		KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_BSLS,
		MT(MOD_MEH,KC_ESC),	KC_A,	KC_R,	KC_S,	KC_T,	KC_G,																KC_M,		KC_N,		KC_E,		KC_I,		KC_O,		KC_QUOT,
		KC_LSFT,			KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	MAGIC_TOGGLE_CTL_GUI,										TO(WIN),	KC_K,		KC_H,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_BSLS),
		_______,	_______,	_______,	_______,	_______,	                                                _______,	_______,	_______,	_______,	_______
	),
	[WIN] = LAYOUT(
		KC_GRV,				KC_1,	KC_2,		KC_3,		KC_4,		KC_5,											KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
		KC_TAB,				KC_Q,	KC_W,		KC_E,		KC_R,		KC_T,											KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_EQL,
		LT(NAV,KC_ESC),	    KC_A,	KC_S,		KC_D,		KC_F,		KC_G,											KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,
		KC_LSFT,			KC_Z,	KC_X,		KC_C,		KC_V,		KC_B,	_______,				    TO(GAME),	KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_DEL),
			MT(MOD_LGUI,KC_LBRC),	_______,	_______,	MO(WINNAV),	CTL_T(KC_BSPC),				_______,	LT(WINNAV, KC_ENT),	_______,	_______,	_______
	),
	[GAME] = LAYOUT(
		KC_GRV,			KC_1,	KC_2,		KC_3,		KC_4,		KC_5,											KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_BSPC,
		KC_TAB,			KC_Q,	KC_W,		KC_E,		KC_R,		KC_T,											KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_BSLS,
		KC_ESC,			KC_A,	KC_S,		KC_D,		KC_F,		KC_G,											KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,
		KC_LSFT,		KC_Z,	KC_X,		KC_C,		KC_V,		KC_B,	_______,					TO(BASE),	KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_LSFT,
			KC_LGUI,	KC_LALT,	MO(NAV),	KC_LCTL,	KC_SPC,								    	KC_SPC,	    MT(MOD_LCTL, KC_ENT), 	MT(MOD_LALT,KC_DEL),	KC_MINS,	KC_EQL
	),
	[SYM]	=	LAYOUT(
		// C(G(KC_SPC)) is the OS X Emoji Editor
		C(G(KC_SPC)),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,											KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,
		KC_BSLS,		KC_BSPC,	KC_EQL,		KC_MINS, 	KC_EQL,		KC_BSPC,										KC_MINS,	KC_P7,		KC_P8,		KC_P9,		KC_NLCK,	KC_F12,
		KC_ENT,			KC_BSLS,	KC_QUOT,	KC_SCLN,	KC_QUOT,	KC_BSLS,										KC_PLUS,	KC_P4,		KC_P5,		KC_P6,		KC_0,		KC_PSCR,
		_______,		KC_SLSH,	KC_DOT,		KC_COMM,	KC_DOT,		KC_SLSH,	C(G(KC_SPC)),			TG(SYM),	KC_ASTR,	KC_P1,		KC_P2,		KC_P3,		KC_BSLS,	KC_NLCK,
									KC_NO,		KC_NO,		TT(SYM),	_______,	_______,				_______,	_______,	TG(SYM),		KC_0,		KC_DOT
	),
	[NAV]=LAYOUT(
		C(KC_GRV),	G(KC_SLSH),	KC_NO,		KC_WH_U,	KC_WH_R,	G(KC_ENT),										KC_NO,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MUTE,	KC_DEL,
		G(KC_TAB),	A(KC_BSPC),	KC_PGUP,	KC_UP,		KC_ENT,		A(KC_DEL),										KC_NO,		KC_BTN5,	KC_MS_U,	KC_BTN4,	KC_END,		KC_LALT,
		C(KC_TAB),	A(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	A(KC_RGHT),										KC_WH_L,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_R,	KC_LGUI,
		KC_LSFT,	KC_HOME,	KC_PGDN,	G(KC_ENT),	KC_SPC,		KC_END,	    G(KC_ENT),				TO(GAME),	KC_NO,		KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_BSLS,	KC_LSFT,
					MT(MOD_LCTL,KC_COMM),	MT(MOD_LALT,KC_DOT),	_______,	_______,A(KC_BSPC),		KC_BTN1,	KC_BTN2,	KC_BTN3,	KC_LBRC,	KC_RBRC
	),
	[WINNAV]=LAYOUT(
		C(KC_GRV),	MEH(2),		KC_NO,		KC_WH_U,	KC_WH_R,	G(KC_ENT),											KC_NO,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MUTE,	KC_LCTL,
		ALT_TAB,  C(KC_BSPC),	KC_PGUP,	KC_UP,		KC_ENT,		A(KC_DEL),											KC_NO,		KC_BTN5,	KC_MS_U,	KC_BTN4,	KC_END,		KC_LALT,
		C(KC_TAB),	C(KC_LEFT), KC_LEFT,	KC_DOWN,	KC_RGHT,	C(KC_RGHT),										 	KC_WH_L,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_R,	KC_LGUI,
		KC_LSFT,	KC_HOME,	KC_PGDN,	KC_SPC,		KC_SPC,		KC_END,		G(KC_ENT),					TG(GAME),	KC_NO,		KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_BSLS,	KC_LSFT,
								MT(MOD_LCTL,KC_COMM),	MT(MOD_LALT,KC_DOT),_______,_______,C(KC_BSPC),		KC_BTN1,	KC_BTN2,	KC_BTN3,	KC_LPRN,	KC_RPRN
	)
};


enum combo_events {
	LPAREN,
	RPAREN,
	PAREN,
	CMD_BSPC,
	CMD_ENTER,
	CTRLC,
	CTRLR,
	CAL,
	APW,
	DELWD,
	EML,
	PHONE,
	EMA,
	COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM asdf_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM zxcv_combo[] = {KC_Z, KC_X, KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM uiop_combo[] = {KC_U, KC_I, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM jklsemi_combo[] = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM mcommdotslsh_combo[] = {KC_M, KC_COMM, KC_DOT, KC_SLSH, COMBO_END};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};

const uint16_t PROGMEM cal_combo[] = {KC_C, KC_A, KC_L, COMBO_END};
const uint16_t PROGMEM phone_combo[] = {KC_P, KC_Q,COMBO_END};
const uint16_t PROGMEM eml_combo[] = {KC_E, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM ema_combo[] = {KC_E, KC_A, KC_M, COMBO_END};



combo_t key_combos[] = {
	[LPAREN] = COMBO_ACTION(zx_combo),
	[PAREN] = COMBO_ACTION(xc_combo),
	[RPAREN] = COMBO_ACTION(cv_combo),
	[CTRLC] = COMBO_ACTION(zxcv_combo),
	[CMD_BSPC] = COMBO_ACTION(jklsemi_combo),
	[CMD_ENTER] = COMBO_ACTION(asdf_combo),
	[CTRLR] = COMBO_ACTION(qr_combo),
	[CAL] = COMBO_ACTION(cal_combo),
	[APW] = COMBO_ACTION(uiop_combo),
	[EML]= COMBO_ACTION(eml_combo),
	[PHONE]= COMBO_ACTION(phone_combo),
	[EMA] = COMBO_ACTION(ema_combo),
	[DELWD] = COMBO_ACTION(df_combo)
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
	switch(combo_index) {

		case DELWD:
			if (pressed) {
				tap_code16(A(KC_BSPC));
			}
			break;
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
				SEND_STRING("https://felixsargent.com/calendar");
				}
			break;
		case EML:
			if (pressed) {
				SEND_STRING("felix.sargent@gmail.com");
				}
			break;
		case EMA:
			if (pressed) {
				SEND_STRING("fsargent@atlassian.com");
				}
			break;
		case PHONE:
			if (pressed) {
				SEND_STRING("4158606970");
				}
			break;
		case APW:
			if (pressed) {
				SEND_STRING("XXX");
				}
			break;
		case CMD_BSPC:
			if (pressed) {
			 tap_code16(G(KC_BSPC));
						}
			break;
		case CMD_ENTER:
			if (pressed) {
			 tap_code16(G(KC_ENT));
					}
			break;
	}
}



uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(state)) {
		case GAME:
			autoshift_disable();
		break;
		default:
			autoshift_enable();
			break;
	}
// 		// rgblight_set_layer_state(2, layer_state_cmp(state, 2));
// 		// rgblight_set_layer_state(3, layer_state_cmp(state, 1));
// 		// rgblight_set_layer_state(4, layer_state_cmp(state, 5));
// 		// rgblight_set_layer_state(5, layer_state_cmp(state, 4));
// 		// rgblight_set_layer_state(6, layer_state_cmp(state, 3));

	return state;
}
