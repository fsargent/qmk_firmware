

#ifdef COMBO_ENABLE


enum combo_events {
	BKT,
	CBRC,
	PAREN,
	LTGT,
	CTRLALTDEL,
	CMD_ENTER,
  ENTER,
  TAB,
  SHIFT_TAB,
	CTRLC,
	CTRLR,
	CAL,
	APW,
	DELWD,
	EML,
	PHONE,
	EMW,
	WINDELWD,
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
const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM qr_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {KC_F, KC_G, COMBO_END};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};


const uint16_t PROGMEM cal_combo[] = {KC_C, KC_A, KC_L, COMBO_END};
const uint16_t PROGMEM phone_combo[] = {KC_P, KC_Q,COMBO_END};
const uint16_t PROGMEM eml_combo[] = {KC_E, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM ema_combo[] = {KC_E, KC_A, KC_M, COMBO_END};


combo_t key_combos[] = {

	// 2 key combos
	[TAB] = COMBO_ACTION(cv_combo),
	[SHIFT_TAB] = COMBO_ACTION(xc_combo),
	// [CBRC] = COMBO_ACTION(cv_combo),
	[LTGT] = COMBO_ACTION(vb_combo),
	[CTRLR] = COMBO_ACTION(qr_combo),
	[DELWD] = COMBO_ACTION(df_combo),
	[WINDELWD] = COMBO_ACTION(fg_combo),

  [ENTER] = COMBO_ACTION(jk_combo),


	// 4 key combos
	[CTRLC] = COMBO_ACTION(zxcv_combo),
	[CTRLALTDEL] = COMBO_ACTION(jklsemi_combo),
	[CMD_ENTER] = COMBO_ACTION(asdf_combo),
	[APW] = COMBO_ACTION(uiop_combo),

	// Misc
	[CAL] = COMBO_ACTION(cal_combo),
	[EML]= COMBO_ACTION(eml_combo),
	[PHONE]= COMBO_ACTION(phone_combo),
	[EMW] = COMBO_ACTION(ema_combo)
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
	switch(combo_index) {

		case ENTER:
			if (pressed) {
				tap_code16(KC_ENTER);
			}
			break;
		case DELWD:
			if (pressed) {
				tap_code16(A(KC_BSPC));
			}
			break;
		case WINDELWD:
			if (pressed) {
				tap_code16(C(KC_BSPC));
			}
			break;
		case TAB:
			if (pressed) {
				tap_code16(KC_TAB);
			}
			break;
		case CBRC:
			if (pressed) {
				SEND_STRING("{}");
				tap_code16(KC_LEFT);
			}
			break;
		case SHIFT_TAB:
			if (pressed) {
				 tap_code16(S(KC_TAB));
			}
			break;
		case LTGT:
			if (pressed) {
				SEND_STRING("<>");
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
		case EMW:
			if (pressed) {
				SEND_STRING("felix@truework.com");
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
		case CTRLALTDEL:
			if (pressed) {
			 tap_code16(C(A(KC_DEL)));
						}
			break;
		case CMD_ENTER:
			if (pressed) {
			 tap_code16(G(KC_ENT));
					}
			break;
	}
}

#endif  // COMBO_ENABLE
