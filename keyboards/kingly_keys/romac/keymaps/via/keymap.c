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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_KP_7, KC_KP_8, KC_KP_9, \
		KC_KP_4, KC_KP_5, KC_KP_6, \
		KC_KP_1, KC_KP_2, KC_KP_3, \
		TO(1),   KC_KP_0, KC_KP_DOT\
	),
	[1] = LAYOUT(
		MEH(KC_KP_7), MEH(KC_TRNS), MEH(KC_TRNS), \
		MEH(KC_KP_4), MEH(KC_TRNS), MEH(KC_TRNS), \
		MEH(KC_KP_1), MEH(KC_TRNS), MEH(KC_TRNS), \
		TO(2), MEH(KC_KP_0), MEH(KC_KP_DOT)\
	),
	[2] = LAYOUT(
        HYPR(KC_TRNS), HYPR(KC_TRNS), HYPR(KC_TRNS), \
		HYPR(KC_TRNS), HYPR(KC_TRNS), HYPR(KC_TRNS), \
		HYPR(KC_TRNS), HYPR(KC_TRNS), HYPR(KC_TRNS), \
		TO(0), HYPR(KC_KP_0), HYPR(KC_KP_DOT)\
	)
};
