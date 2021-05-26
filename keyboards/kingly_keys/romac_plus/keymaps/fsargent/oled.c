
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}
#define BASE 0
#define NAV 1
#define SYM 2
#define MEDIA 3
#define WIND 4
#define MOUSE 5

void oled_task_user(void) {
//   Host Keyboard Layer Status
  switch (get_highest_layer(layer_state)) {
    case BASE:
      oled_write_ln_P(PSTR("Num\n"), false);
      oled_write_ln_P(PSTR("7|8|9\n4|5|6\n1|2|3\n@|0|."), false);
      break;
    case NAV:
      oled_write_ln_P(PSTR("Nav\n"), false);
      oled_write_ln_P(PSTR("H|^|U\n<|T|>\nE|v|D\n@|X|E"), false);
      break;
    case SYM:
      oled_write_ln_P(PSTR("Sym\n"), false);
      oled_write_ln_P(PSTR("&|*|(\n$|%|^\n!|@|#\n@|)|E"), false);

      break;
    case MEDIA:
      oled_write_ln_P(PSTR("Mus\n"), false);
      oled_write_ln_P(PSTR("NL||+\n<|P|>\n | |-\n@|M| "), false);
      break;
    case WIND:
      oled_write_ln_P(PSTR("Windo"), false);
      oled_write_ln_P(PSTR(" | | \n | | \n | | \n@| | "), false);
      break;
    case MOUSE:
      oled_write_ln_P(PSTR("Mouse"), false);
      oled_write_ln_P(PSTR("1|^|2\n<|v|>\nl|u|r\n@|d|3"), false);
      break;

    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undef\n"), false);
  }
}
#endif
