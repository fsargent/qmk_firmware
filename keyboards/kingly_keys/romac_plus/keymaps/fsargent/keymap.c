/* Copyright 2018 Jack Humbert
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

#define BASE 0
#define NAV 1
#define SYM 2
#define MEDIA 3
#define WIND 4
#define MOUSE 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
		KC_P7, KC_P8, KC_P9,
		KC_P4, KC_5, KC_P6,
		KC_P1, KC_P2, KC_P3,
		TO(1), KC_P0, KC_PDOT
	),

	[NAV] = LAYOUT(
	    KC_HOME, KC_UP, KC_PGUP,
		KC_LEFT, KC_TAB, KC_RIGHT,
		KC_END, KC_DOWN, KC_PGDN,
		TO(2), KC_DEL, KC_PENT
	),
	[SYM] = LAYOUT(
		KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN,
		KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX,
		KC_EXCLAIM, KC_AT, KC_HASH,
		TO(3), KC_RIGHT_PAREN, KC_PENT
	),
    [MEDIA] = LAYOUT(
		KC_NUMLOCK, KC_NO, KC_AUDIO_VOL_UP,
		KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
		KC_NO, KC_NO, KC_AUDIO_VOL_DOWN,
		TO(4), KC_AUDIO_MUTE, KC_NO
	),
    [WIND] = LAYOUT(
		MEH(KC_W), MEH(KC_E), MEH(KC_R),
		MEH(KC_S), MEH(KC_D), MEH(KC_F),
	    MEH(KC_X), MEH(KC_C), MEH(KC_V),
		TO(5), MEH(KC_B), MEH(KC_G)
	),
    [MOUSE] = LAYOUT(
		KC_BTN1, KC_MS_U, KC_BTN2,
		KC_MS_L, KC_MS_D, KC_MS_R,
		KC_WH_L, KC_WH_U, KC_WH_R,
		TO(0), KC_WH_D, KC_BTN3
	)

};

