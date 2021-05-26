
#ifdef ENCODER_ENABLE

bool     is_alt_tab_active = false;  // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;      // we will be using them soon.

#define BASE 0
#define NAV 1
#define SYM 2
#define MEDIA 3
#define WIND 4
#define MOUSE 5


void matrix_scan_user(void) {  // The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(0)) {  // OS Opt Tab
        if (clockwise) {
            tap_code16(C(KC_UP));
        } else {
            tap_code16(C(KC_DOWN));
        }
    } else if (IS_LAYER_ON(1)) {  // on Raise layer control chrome tab switching
        if (clockwise) {
            tap_code16(A(KC_UP));
        } else {
            tap_code16(A(KC_DOWN));
        }
    } else if (IS_LAYER_ON(2)) {  // on Raise layer control chrome tab switching
          if (clockwise) {
            tap_code16(C(S(KC_UP)));
        } else {
            tap_code16(C((S(KC_DOWN))));
        }
    } else if (IS_LAYER_ON(3)) {  // on Raise layer control chrome tab switching
          if (clockwise) {
            tap_code16(MEH(KC_UP));
        } else {
            tap_code16(MEH(KC_DOWN));
        }
    } else if (IS_LAYER_ON(4)) {  // on Raise layer control chrome tab switching
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
    } else if (IS_LAYER_ON(5)) {  // on Raise layer control chrome tab switching
        if (clockwise) {
            tap_code16(C(S(KC_TAB)));
        } else {
            tap_code16(C(KC_TAB));
        }
    } else {  // on other layers switch windows in OSX
        if (clockwise) {
            tap_code16(G(S(KC_GRV)));
        } else {
            tap_code16(G(KC_GRV));
        }
    }
}
#endif
