
enum combo_events {
    RST,
    TOGWIN,
    TOGGAME,
    MUTE,
    SEL_WORD,
    SEL_LINE,
    CUT,
    CPY,
    PST,
    CAL,
    DELWD,
    QIN,
    KL,
    QNM,
    EML, WRK,
    QP,
    TAB,
    THUMB_NUM,
    SD_GRAVE,
    M_COMMA_MINUS,
    DOT_COMMA_EQL,
    COMBO_LENGTH
};
uint16_t COMBO_LEN		= COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM zxcv_combo[]		= {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM mute_combo[]		= {KC_VOLU,KC_VOLD, COMBO_END};

// LSFT_T(KC_A)
// LGUI_T(KC_S)
// LALT_T(KC_D)
// LCTL_T(KC_F)

const uint16_t PROGMEM zx_combo[]		= {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM jk_combo[]		= {M_J, M_K, COMBO_END};
const uint16_t PROGMEM kl_combo[]		= {M_K, M_L, COMBO_END};
const uint16_t PROGMEM xc_combo[]		= {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[]		= {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[]		= {KC_Q, KC_R, COMBO_END};
// Removed df_combo (Tab handled via sdf_combo)
const uint16_t PROGMEM gravminus_combo[]	= {KC_GRV, KC_DEL, COMBO_END};

// New combos
const uint16_t PROGMEM sd_combo[]		= {M_S, M_D, COMBO_END};
const uint16_t PROGMEM m_comma_combo[]		= {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM dot_comma_combo[]	= {KC_DOT, KC_COMMA, COMBO_END};

const uint16_t PROGMEM xcv_combo[]		= {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM sdf_combo[]		= {LGUI_T(KC_S), LALT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM df_combo[]		= {M_D, M_F, COMBO_END};

const uint16_t PROGMEM cal_combo[]		= {KC_C, M_A, M_L, COMBO_END};
const uint16_t PROGMEM phone_combo[]	= {KC_P, KC_Q, COMBO_END};
const uint16_t PROGMEM qnm_combo[]		= {KC_Q, KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM qin_combo[]		= {KC_Q, KC_I, KC_N, COMBO_END};
const uint16_t PROGMEM eml_combo[]		= {KC_E, KC_M, M_L, COMBO_END};
const uint16_t PROGMEM wrk_combo[]		= {KC_W, KC_R, MT(MOD_LGUI, KC_K), COMBO_END};
// Removed rbu and rbl combos

const uint16_t PROGMEM togwin_combo[]		= {KC_9, KC_2, COMBO_END};
const uint16_t PROGMEM toggame_combo[]		= {KC_0, KC_1, COMBO_END};
const uint16_t PROGMEM tog_num_combo[]		= {KC_KP_0,	KC_PDOT, COMBO_END};

// get_tapping_term moved to keymap.c for per-key tuning

combo_t key_combos[]	= {
    // Simple key outputs
    [MUTE]          = COMBO(mute_combo, KC_MUTE),
    [SD_GRAVE]      = COMBO(sd_combo, KC_GRV),
    [M_COMMA_MINUS] = COMBO(m_comma_combo, KC_MINS),
    [DOT_COMMA_EQL] = COMBO(dot_comma_combo, KC_EQL),
    [KL]            = COMBO(kl_combo, KC_ENT),
    [TAB]           = COMBO(df_combo, KC_TAB),

    // Action combos
    [CUT]		= COMBO_ACTION(zx_combo),
    [CPY]		= COMBO_ACTION(xc_combo),
    [PST]		= COMBO_ACTION(cv_combo),
    [DELWD]		= COMBO_ACTION(jk_combo),
    [RST]		= COMBO_ACTION(gravminus_combo),

    [TOGGAME]	= COMBO_ACTION(toggame_combo),
    [TOGWIN]	= COMBO_ACTION(togwin_combo),

    // 3–4 key actions
    [SEL_WORD]	= COMBO_ACTION(xcv_combo),
    [SEL_LINE]	= COMBO_ACTION(zxcv_combo),

    // Misc strings
    [CAL]		= COMBO_ACTION(cal_combo),
    [EML]		= COMBO_ACTION(eml_combo),
    [WRK]		= COMBO_ACTION(wrk_combo),
    [QP]		= COMBO_ACTION(phone_combo),
    [QIN]		= COMBO_ACTION(qin_combo),
    [QNM]		= COMBO_ACTION(qnm_combo),
    [THUMB_NUM]	= COMBO_ACTION(tog_num_combo),
};

/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

#if 0
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CUT:
            if (pressed) { send_os_shortcut_ctrlgui(KC_X); }
            break;
        case CPY:
            if (pressed) { send_os_shortcut_ctrlgui(KC_C); }
            break;
        case PST:
            if (pressed) { send_os_shortcut_ctrlgui(KC_V); }
            break;
        case DELWD:
            if (pressed) { send_os_delete_word(); }
            break;
        case SEL_LINE:
            if (pressed) {
                if (is_apple_os()) {
                    SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LGUI));
                } else {
                    SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
                }
            }
            break;
        case SEL_WORD:
            if (pressed) {
                if (is_apple_os()) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL));
                }
            }
            break;
        case THUMB_NUM:
            if (pressed) { layer_invert(_NUM); }
            break;
        case RST:
            if (pressed) { reset_keyboard(); }
            break;
        case TOGWIN:
            if (pressed) { layer_move(_WIN); }
            break;
        case TOGGAME:
            if (pressed) { layer_move(_GAME); }
            break;
        case QNM:
            if (pressed) { SEND_STRING("Felix Sargent"); }
            break;
        case QIN:
            if (pressed) { SEND_STRING("https://linkedin.com/in/felixsargent"); }
            break;
        case CAL:
            if (pressed) { SEND_STRING("https://felixsargent.com/calendar"); }
            break;
        case EML:
            if (pressed) { SEND_STRING("felix.sargent@gmail.com"); }
            break;
        case WRK:
            if (pressed) { SEND_STRING("fsargent@recruitbot.com"); }
            break;
        case QP:
            if (pressed) { SEND_STRING("4158606970"); }
            break;
    }
}
#endif

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CUT:
            if (pressed) { send_os_shortcut_ctrlgui(KC_X); }
            break;
        case CPY:
            if (pressed) { send_os_shortcut_ctrlgui(KC_C); }
            break;
        case PST:
            if (pressed) { send_os_shortcut_ctrlgui(KC_V); }
            break;
        case DELWD:
            if (pressed) { send_os_delete_word(); }
            break;
        case SEL_LINE:
            if (pressed) {
                if (is_apple_os()) {
                    SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LGUI));
                } else {
                    SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
                }
            }
            break;
        case SEL_WORD:
            if (pressed) {
                if (is_apple_os()) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL));
                }
            }
            break;
        case THUMB_NUM:
            if (pressed) { layer_invert(_NUM); }
            break;
        case RST:
            if (pressed) { reset_keyboard(); }
            break;
        case TOGWIN:
            if (pressed) { layer_move(_WIN); }
            break;
        case TOGGAME:
            if (pressed) { layer_move(_GAME); }
            break;
        case QNM:
            if (pressed) { SEND_STRING("Felix Sargent"); }
            break;
        case QIN:
            if (pressed) { SEND_STRING("https://linkedin.com/in/felixsargent"); }
            break;
        case CAL:
            if (pressed) { SEND_STRING("https://felixsargent.com/calendar"); }
            break;
        case EML:
            if (pressed) { SEND_STRING("felix.sargent@gmail.com"); }
            break;
        case WRK:
            if (pressed) { SEND_STRING("fsargent@recruitbot.com"); }
            break;
        case QP:
            if (pressed) { SEND_STRING("4158606970"); }
            break;
    }
}


