// if (layer_state_is(0)) {
// 	switch (combo_index) {
// 		case DELWD:
// 			if (pressed) {
// 				tap_code16(A(KC_BSPC));
// 			}
// 			break;
// 		case CUT:
// 			if (pressed) {
// 				tap_code16(G(KC_X));
// 			}
// 			break;
// 		case CPY:
// 			if (pressed) {
// 				tap_code16(G(KC_C));
// 			}
// 			break;
// 		case PST:
// 			if (pressed) {
// 				tap_code16(G(KC_V));
// 			}
// 			break;
// 		case SEL_LINE:
// 			if (pressed) {
// 				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LGUI));
// 			}
// 			break;
// 		case SEL_WORD:
// 			if (pressed) {
// 				SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT));
// 			}
// 	}
// }
// if (layer_state_is(1)) {
// 	switch (combo_index) {
// 		case DELWD:
// 			if (pressed) {
// 				tap_code16(C(KC_BSPC));
// 			}
// 			break;
// 		case CUT:
// 			if (pressed) {
// 				tap_code16(C(KC_X));
// 			}
// 			break;
// 		case CPY:
// 			if (pressed) {
// 				tap_code16(C(KC_C));
// 			}
// 			break;
// 		case PST:
// 			if (pressed) {
// 				tap_code16(C(KC_V));
// 			}
// 			break;
// 		case WINTGSYM:
// 			if (pressed) {
// 				layer_invert(3);
// 			}
// 			break;
// 		case SEL_LINE:
// 			if (pressed) {
// 				SEND_STRING( SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
// 			}
// 			break;
// 		case SEL_WORD:
// 			if (pressed) {
// 				SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL));
// 			}
// 	}
// }
// switch (combo_index) {
// 	case RST:
// 		if (pressed) {
// 			reset_keyboard();
// 		}
// 		break;
// 	case TGSYM:
// 		if (pressed) {
// 			layer_invert(3);
// 		}
// 		break;
// 	case CAL:
// 		if (pressed) {
// 			SEND_STRING("https://felixsargent.com/calendar");
// 		}
// 		break;
// 	case EML:
// 		if (pressed) {
// 			SEND_STRING("felix.sargent@gmail.com");
// 		}
// 		break;
// 	case EMW:
// 		if (pressed) {
// 			SEND_STRING("felix@truework.com");
// 		}
// 		break;
// 	case PHONE:
// 		if (pressed) {
// 			SEND_STRING("4158606970");
// 		}
// 		break;
// 	case CTRLALTDEL:
// 		if (pressed) {
// 			tap_code16(C(A(KC_DEL)));
// 		}
// 		break;
// }
