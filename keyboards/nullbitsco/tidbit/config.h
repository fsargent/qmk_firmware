/* Copyright 2021 Jay Greco
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
#pragma once

#include "config_common.h"

<<<<<<< HEAD
/* Used to set slave for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_SLAVE

// Workaround for freezing after MacOS sleep
#define NO_USB_STARTUP_CHECK

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6E61
#define PRODUCT_ID      0x6061
#define DEVICE_VER      0x0001
#define MANUFACTURER    nullbits
#define PRODUCT         TIDBIT
#define DESCRIPTION     QMK keyboard firmware
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, E6, D7, C6, D4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7 }
#define UNUSED_PINS
=======
/* Used to set remote for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_REMOTE

// Workaround for freezing after MacOS sleep
#define USB_SUSPEND_WAKEUP_DELAY 200

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, E6, D7, C6, D4 }
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, F4, F5, F6, F7 }
>>>>>>> origin/master

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Optional SMT LED pins */
#define RGB_DI_PIN B6
#define RGBLED_NUM 8
<<<<<<< HEAD
#define RGBLIGHT_ANIMATIONS

/* Additional optional encoder pins */

// You can mix/match pins within the ENCODERS_PAD_A and ENCODERS_PAD_B defines.

// Encoder 1 Pins:
// #define ENCODERS_PAD_A { B3 }
// #define ENCODERS_PAD_B { B2 }

// Encoder 2 Pins:
// #define ENCODERS_PAD_A { B4 }
// #define ENCODERS_PAD_B { B5 }

// Encoder 3 Pins: ⚠️ Compatibility note: encoder 3 shares the drive signals with the I2C bus. It can not be used at the same time as the OLED, alphanumeric display, or LED matrix options.
// #define ENCODERS_PAD_A { D0 }
// #define ENCODERS_PAD_B { D1 }

// Encoder 4 Pins: ⚠️ Compatibility note: encoder 4 shares the drive signals with the UART bus. It can not be used at the same time as the expansion port.
// #define ENCODERS_PAD_A { D2 }
// #define ENCODERS_PAD_B { D3 }
=======
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

/* Optional encoder pins */
// Encoders are defined in order. 1: B2 & B3, 2: B4 & B5, 3: D0 & D1, 4: D2 & D3
#define ENCODERS_PAD_A { B2, B4, D0, D3 }
#define ENCODERS_PAD_B { B3, B5, D1, D2 }
>>>>>>> origin/master
