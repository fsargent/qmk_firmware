/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

// No need for the single versions when multi performance isn't a problem =D
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH

// 20m timeout (20m * 60s * 1000mil)
// #define RGB_DISABLE_TIMEOUT 1200000
#define RGB_DISABLE_TIMEOUT 1200000
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define STM32_ONBOARD_EEPROM_SIZE 2048

// Mouse Keys - Constant Speed Mode (no acceleration by default)
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

// Speed settings: MS_ACL0 (j) = super fast, MS_ACL1 (k) = faster, unmodified = default, MS_ACL2 (;) = super slow
// MS_ACL0 - Super fast
#define MK_C_OFFSET_0       64      // Cursor offset per movement
#define MK_C_INTERVAL_0     16      // Time between cursor movements

// MS_ACL1 - Faster
#define MK_C_OFFSET_1       32      // Cursor offset per movement
#define MK_C_INTERVAL_1     16      // Time between cursor movements

// Unmodified - Default medium speed (l key will use this)
#define MK_C_OFFSET_UNMOD   16      // Cursor offset per movement
#define MK_C_INTERVAL_UNMOD 16      // Time between cursor movements

// MS_ACL2 - Super slow
#define MK_C_OFFSET_2       4       // Cursor offset per movement
#define MK_C_INTERVAL_2     32      // Time between cursor movements

// Mouse wheel settings
#define MK_W_OFFSET_0       1
#define MK_W_INTERVAL_0     40
#define MK_W_OFFSET_1       1
#define MK_W_INTERVAL_1     80
#define MK_W_OFFSET_UNMOD   1
#define MK_W_INTERVAL_UNMOD 120
#define MK_W_OFFSET_2       1
#define MK_W_INTERVAL_2     240


#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define QUICK_TAP_TERM 125
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define ENCODER_RESOLUTION 4
#define ENCODER_MAP_KEY_DELAY 10

// Combo timing improvements
#define COMBO_STRICT_TIMER
// You can also tune COMBO_TERM here if desired (defaults usually fine)
