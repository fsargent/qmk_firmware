#include QMK_KEYBOARD_H
// #include "action_layer.h"
// #include "../common/remote_kb.h"
// #include "../common/bitc_led.h"
// Tab size = 6

#define _BASE	0
#define _NAV	1
#define _MUSIC	2
#define _FN		3
#define _FN2	4
#define _FUNC	5


enum custom_keycodes {
	PROG = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Base layer (numpad)
	[_BASE] = LAYOUT(
								KC_NUM_LOCK,	KC_ESC,		KC_KP_ENTER, \
	TO(_FUNC),	TO(_NAV),	KC_KP_SLASH,	KC_KP_7,		KC_KP_8,		KC_KP_9,\
	KC_NO,	KC_NO,	KC_KP_ASTERISK,	KC_KP_4,		KC_KP_5,		KC_KP_6,\
	KC_NO,	KC_NO,	KC_KP_MINUS,	KC_KP_1,		KC_KP_2,		KC_KP_3,\
	KC_NO,	KC_NO,	KC_KP_PLUS,		KC_PEQL,		KC_KP_0,		KC_KP_DOT\
	),
	[_NAV] = LAYOUT(
				QK_MAGIC_SWAP_LCTL_LGUI,	KC_LPRN,	KC_RPRN,\
	TO(_BASE),	TO(_MUSIC),	C(KC_Z),	KC_HOME,	KC_UP,	KC_PGUP,\
	KC_NO,	KC_NO,	S(C(KC_Z)),	KC_LEFT,	KC_BSPC,	KC_RIGHT,\
	KC_NO,	KC_NO,	KC_BSPC,	KC_END,	KC_DOWN,	KC_PGDN,\
	KC_NO,	KC_NO,	KC_SPC,	KC_TAB,	KC_SPC,	KC_DEL
	),
	[_MUSIC] = LAYOUT(
							KC_MUTE,	KC_MUTE,	KC_MUTE, \
	TO(_NAV),	TO(_FN),	_______,	KC_VOLU,	KC_VOLU,	KC_VOLU,\
	KC_NO,	KC_NO,	_______,	KC_MPRV,	KC_MPLY,	KC_MNXT,\
	KC_NO,	KC_NO,	_______,	KC_VOLD,	KC_VOLD,	KC_VOLD,\
	KC_NO,	KC_NO,	_______,	KC_LALT,	KC_LCTL,	KC_LGUI\
	),
	[_FN] = LAYOUT(
							KC_F10,	KC_F11,	KC_F12, \
	TO(_MUSIC),	TO(_FN2),	_______,	KC_F7,	KC_F8,	KC_F9,\
	KC_NO,	KC_NO,	_______,	KC_F4,	KC_F5,	KC_F6,\
	KC_NO,	KC_NO,	_______,	KC_F1,	KC_F2,	KC_F3,\
	KC_NO,	KC_NO,	_______,	KC_LALT,	KC_LCTL,	KC_LGUI\
	),
	[_FN2] = LAYOUT(
							KC_F22,	KC_F23,	KC_F24, \
	TO(_FN),	TO(_FUNC),	_______,	KC_F19,	KC_F20,	KC_F21,\
	KC_NO,	KC_NO,	_______,	KC_F16,	KC_F17,	KC_F18,\
	KC_NO,	KC_NO,	_______,	KC_F13,	KC_F14,	KC_F15,\
	KC_NO,	KC_NO,	_______,	KC_LALT,	KC_LCTL,	KC_LGUI\
	),
	// Function layer (numpad)
	[_FUNC] = LAYOUT(
							QK_BOOT,	RGB_TOG,	KC_NO,
	TO(_FN2),	TO(_BASE),	_______,	KC_NO,	RGB_MOD,	KC_NO,
	KC_NO,	KC_NO,	_______,	KC_NO,	RGB_HUI,	KC_NO,
	KC_NO,	KC_NO,	_______,	KC_NO,	RGB_SAI,	KC_NO,
	KC_NO,	KC_NO,	_______,	KC_NO,	RGB_VAI,	KC_NO
	),
};

//
// bool encoder_update_user(uint8_t index, bool clockwise) {
	// /* With an if statement we can check which encoder was turned. */
	// switch (get_highest_layer(layer_state)) {
	// case 1:
		// if (index == 0) {
			// if (clockwise) {
				// tap_code(KC_VOLU);
			// } else {
				// tap_code(KC_VOLD);
			// }
		// }
		// else { /* Second encoder */
			// if (clockwise) {
				// tap_code16(KC_MNXT);
			// } else {
				// tap_code16(KC_MPRV);
			// }
		// }
		// break;
	// default:
		// if (index == 0) { /* First encoder */
			// if (clockwise) {
				// tap_code(KC_UP);
			// } else {
				// tap_code(KC_DOWN);
			// }
		// } else { /* Second encoder */
			// if (clockwise) {
				// tap_code16(KC_RIGHT);
			// } else {
				// tap_code16(KC_LEFT);
			// }
		// }
	// }
	// return true;
// };
//
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

layer_state_t layer_state_set_user(layer_state_t state) {
    // Clear OLED display before changing the layer
    oled_clear();
    return state;
}


static void print_status_narrow(void) {

	// Print current layer
	// enum layers { NUM, NAV, FN };
	led_t led_state = host_keyboard_led_state();
	switch (get_highest_layer(layer_state)) {
		case 0:
			oled_write_ln_P(PSTR("Num"), false);
			oled_write_P(PSTR("/|*|-"), false);
			oled_write_P(PSTR("7|8|9"), false);
			oled_write_P(PSTR("4|5|6"), false);
			oled_write_P(PSTR("1|2|3"), false);
			oled_write_P(PSTR("A|C|G"), false);
			break;
		case 1:
			oled_write_ln_P(PSTR("Nav"), true);
			oled_write_P(PSTR("9PgUp"), false);
			oled_write_P(PSTR("8-Up\n"), false);
			oled_write_P(PSTR("7Home"), false);
			oled_write_P(PSTR("6->\n"), false);
			oled_write_P(PSTR("5=\n"), false);
			oled_write_P(PSTR("4<-\n"), false);
			oled_write_P(PSTR("3PgDn"), false);
			oled_write_P(PSTR("2Dn\n"), false);
			oled_write_P(PSTR("1End\n"), false);
			oled_write_P(PSTR(".Del\n"), false);
			oled_write_P(PSTR("0spc\n"), false);
			oled_write_P(PSTR("=Tab\n"), false);
			break;
		case 2:
			oled_write_ln_P(PSTR("Fn"), true);
			oled_write_P(PSTR("10-12"), false);
			oled_write_P(PSTR("7|8|9"), false);
			oled_write_P(PSTR("4|5|6"), false);
			oled_write_P(PSTR("1|2|3"), false);
			break;
		case 3:
			oled_write_ln_P(PSTR("Fn2"), false);
			oled_write_P(PSTR("22-24"), false);
			oled_write_P(PSTR("19-21"), false);
			oled_write_P(PSTR("16-18"), false);
			oled_write_P(PSTR("13-15"), false);
			break;
		case 4:
			oled_write_P(PSTR("Music"), false);
			oled_write_P(PSTR("Mute "), false);
			oled_write_P(PSTR("VolUp"), false);
			oled_write_P(PSTR("< P >"), false);
			oled_write_P(PSTR("VolDn"), false);
			break;
		 case 5:
			oled_write_ln_P(PSTR("RGB\n"), false);
			oled_write_P(PSTR("RESET"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR("Mode"), false);
			oled_write_ln_P(PSTR("Hue"), false);
			oled_write_ln_P(PSTR("Sat"), false);
			oled_write_ln_P(PSTR("Val"), false);
			break;
		default:
			oled_write_ln_P(PSTR("Undef"), false);
	}
	oled_write_ln_P(PSTR(""), false);
	oled_write_ln_P(led_state.num_lock ? PSTR("Num") : PSTR("<-->"), !led_state.num_lock );
	oled_write_ln_P(get_mods() & MOD_BIT(KC_LCTL) ? PSTR("WIN") : PSTR("OSX"), false);
}

bool oled_task_user(void) {
	print_status_narrow();
	return false;
}

#endif

//
// void matrix_init_user(void) {
	// matrix_init_remote_kb();
	// register_code(KC_NLCK);
// }
//
// void matrix_scan_user(void) {
	// matrix_scan_remote_kb();
// }
//
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	// process_record_remote_kb(keycode, record);
	// switch(keycode) {
		// case PROG:
			// if (record->event.pressed) {
				// set_bitc_LED(LED_DIM);
				// rgblight_disable_noeeprom();
				// bootloader_jump(); //jump to bootloader
			// }
		// break;
//
		// default:
		// break;
	// }
	// return true;
// }


// layer_state_t layer_state_set_user(layer_state_t state) {
// 		switch (get_highest_layer(state)) {
// 		case _FUNC:
// 				unregister_code(KC_NLCK);
// 				break;
// 		default: //	for any other layers, or the default layer
// 				register_code(KC_NLCK);
// 				break;
// 		}
// 	return state;
// }

//
//
//
// void led_set_kb(uint8_t usb_led) {
	// if (usb_led & (1<<USB_LED_NUM_LOCK))
		// set_bitc_LED(LED_DIM);
	// else
		// set_bitc_LED(LED_OFF);
// }
//
//
//
// enum combo_events {
	// RST,
	// PRT,
	// COMBO_LENGTH
// };
// uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!
//
// const uint16_t PROGMEM reset_combo[] = {KC_KP_ENTER, KC_ESC, COMBO_END};
// const uint16_t PROGMEM prt_combo[] = {KC_KP_1,KC_KP_2, COMBO_END};
//
//
// combo_t key_combos[] = {
//
	// [RST] = COMBO_ACTION(reset_combo),
	// [PRT] = COMBO_ACTION(prt_combo)
//
	// Lock computer combo!
// };
// /* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */
//
// void process_combo_event(uint16_t combo_index, bool pressed) {
	// switch(combo_index) {
//
		// case RST:
			// if (pressed) {
				// set_bitc_LED(LED_DIM);
				// rgblight_disable_noeeprom();
				// bootloader_jump(); //jump to bootloader
			// }
			// break;
		// case PRT:
			// if (pressed) {
				// SEND_STRING("hello");
			// }
			// break;
	// }
// }
//
