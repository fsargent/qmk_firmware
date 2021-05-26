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

// Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.

#ifdef ENCODER_ENABLE

bool     is_alt_tab_active = false;  // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;      // we will be using them soon.

void matrix_scan_user(void) {  // The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 500) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        if (IS_LAYER_ON(0)) {  // on Raise layer control up down scrolling
            if (clockwise) {
                tap_code(KC_UP);
            } else {
                tap_code(KC_DOWN);
            }
        } else {  // on other layers emulate left right scrolling
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
        }
    } else if (index == 0) {
        if (IS_LAYER_ON(0)) {  // OS Opt Tab

            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LGUI);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LGUI);
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
        } else if (IS_LAYER_ON(3)) {  // on Raise layer controls window
              if (clockwise) {
                tap_code16(G(S(KC_GRV)));
            } else {
                tap_code16(G(KC_GRV));
            }
        } else {  // on other layers chrome tab switching
          if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(C(S(KC_TAB)));
            }
        }
    }
}
#endif
