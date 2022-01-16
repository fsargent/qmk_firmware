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

// Sets up what the OLED screens display.

#ifdef OLED_DRIVER_ENABLE


static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {

    // Print current layer
    // enum layers { BASE,WIN, GAME, SYM, NAV, WINNAV};

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("OS X\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("WIN\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("GAME\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("SYM\n"), true);
            break;
        case 5:
            oled_write_P(PSTR("NAV\n"), true);
            break;
        case 6:
            oled_write_P(PSTR("W NAV"), true);
            break;


        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("SWAP"), true);
    } else {
        oled_write_ln_P(PSTR("SWAP"), false);
    }
    // led_t led_usb_state = host_keyboard_led_state();
    // oled_write_ln_P(PSTR("\n\n\n\n\n\n\n//\nFelix"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}



void render_mod_status(void) {
    bool blink = (timer_read() % 1000) < 500;
    uint8_t modifiers = get_mods();
        if (modifiers & MOD_MASK_SHIFT & MOD_MASK_ALT & MOD_MASK_CTRL) {
            oled_write_ln_P(blink ? PSTR("$meh_") : PSTR("$meh "), false);
        } else if (modifiers & MOD_MASK_CTRL) {
            oled_write_ln_P(blink ? PSTR("$ctl_") : PSTR("$ctl "), false);
        } else if (modifiers & MOD_MASK_SHIFT) {
            oled_write_ln_P(blink ? PSTR("$sft_") : PSTR("$sft "), false);
		} else if (modifiers & MOD_MASK_ALT) {
            oled_write_ln_P(blink ? PSTR("$alt_") : PSTR("$alt "), false);
        } else if (modifiers & MOD_MASK_GUI) {
            oled_write_ln_P(blink ? PSTR("$gui_") : PSTR("$gui "), false);
        } else {
            oled_write_ln_P(blink ? PSTR("$_  ") : PSTR("$    "), false);
        }
}


void oled_task_user(void) {

    if (is_keyboard_master()) {
        print_status_narrow();
        oled_set_cursor(0,5);
	    render_mod_status();
	    oled_set_cursor(0,13);

    } else {
        render_logo();
    }
}

#endif
