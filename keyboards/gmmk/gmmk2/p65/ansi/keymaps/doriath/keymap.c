#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    // U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    // U_T_AGCR,              //USB Toggle Automatic GCR control
    // DBG_TOG,               //DEBUG Toggle On / Off
    // DBG_MTRX,              //DEBUG Toggle Matrix Prints
    // DBG_KBD,               //DEBUG Toggle Keyboard Prints
    // DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT = SAFE_RANGE,               //Restart into bootloader after hold timeout
    // QMK,                   //Nav to QMK folder
    // COMP,                  //QMK compile command for keyboard massdrop CTRL and keymap phonevon
    // LOAD,                  //mdload script command
  TNOB,  // orange, blue
  TNBO,  // blue, orange
  ORNG, // orange
  BLUE,  // blue
  GRNP,  // green, pink
  MIAMI,  // blue, pink
  XMAS,  // green, red
  SAMX,  // red, green
  CYAN,  // cyan
  JAN,
  FEB,
  MAR,
  APR,
  MAY,
  JUN,
  JUL,
  AUG,
  SEP,
  OCT,
  NOV,
  DEC,
  CYCLE_lra,
  CYCLE_uda,
  RAIN_mcha,
  CYCLE_oia
};


/* 
 * GMMK 2 Compact ANSI
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_HOME,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_END,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT),

[1] = LAYOUT(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  KC_INS,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  MD_BOOT,  _______,
  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,            RGB_VAI,  KC_PGUP,
  _______,  _______,  _______,                                _______,                                TG(2),    _______,  RGB_RMOD, RGB_VAD,  RGB_MOD),

[2] = LAYOUT(
  TO(0),    CYCLE_lra,CYCLE_uda,RAIN_mcha,CYCLE_oia,RGB_TOG,  XXXXXXX,  KC_P7,    KC_P8,    KC_P9,    KC_PSLS,  KC_PAST,  XXXXXXX,  _______, _______,
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  EE_CLR,   XXXXXXX,  XXXXXXX,  KC_P4,    KC_P5,    KC_P6,    KC_PMNS,  XXXXXXX,  XXXXXXX,  _______, _______,
  _______,  KC_A,     KC_S,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_P1,    KC_P2,    KC_P3,    KC_PPLS,  KC_NUM,   _______,           _______,
  _______,  KC_Z,     KC_X,     KC_C,     KC_V,     XXXXXXX,  XXXXXXX,  KC_P0,    KC_PDOT,  KC_PENT,  XXXXXXX,  _______,            KC_UP,   _______,
  _______,  _______,  _______,                                _______,                                _______,  _______,  KC_LEFT,  KC_DOWN, KC_RGHT)
};



#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint32_t key_timer;

  switch (keycode) {
  case MD_BOOT:
    if (record -> event.pressed) {
      key_timer = timer_read32();
    } else {
      if (timer_elapsed32(key_timer) >= 500) {
        reset_keyboard();
      }
    }
    return false;
  case RGB_TOG:
    if (record -> event.pressed) {
      switch (rgb_matrix_get_flags()) {
      case LED_FLAG_ALL: {
        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
        rgb_matrix_set_color_all(0, 0, 0);
      }
      break;
      case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
        rgb_matrix_set_color_all(0, 0, 0);
      }
      break;
      case LED_FLAG_UNDERGLOW: {
        rgb_matrix_set_flags(LED_FLAG_NONE);
        rgb_matrix_disable_noeeprom();
      }
      break;
      default: {
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_enable_noeeprom();
      }
      break;
      }
    }
    return false;





  case JAN:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(87, 255, 255); //set HSV 
    } else {}
    return false;

  case FEB:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(0, 255, 255); //set HSV 
    } else {}
    return false;

  case MAR:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(98, 255, 255); //set HSV 
    } else {}
    return false;

  case APR:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(130, 255, 255); //set HSV 
    } else {}
    return false;

  case MAY:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(160, 255, 255); //set HSV 
    } else {}
    return false;

  case JUN:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(165, 255, 255); //set HSV 
    } else {}
    return false;

  case JUL:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(170, 255, 255); //set HSV 
    } else {}
    return false;

  case AUG:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(30, 255, 255); //set HSV 
    } else {}
    return false;

  case SEP:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(20, 255, 255); //set HSV 
    } else {}
    return false;

  case OCT:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(10, 255, 200); //set HSV 
    } else {}
    return false;

  case NOV:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(0, 255, 170); //set HSV 
    } else {}
    return false;

  case DEC:
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(1); //set mode
      rgb_matrix_sethsv_noeeprom(80, 255, 170); //set HSV 
    } else {}
    return false;



  case CYCLE_lra:
    // RGB_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT); //set mode
      layer_move(0);
    } else {}
    return false;

  case CYCLE_uda:
    // RGB_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_UP_DOWN); //set mode
      layer_move(0);
    } else {}
    return false;

  case RAIN_mcha:
    // RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradient Chevron shapped scrolling left to right
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON); //set mode
      layer_move(0);
    } else {}
    return false;

  case CYCLE_oia:
    // RGB_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
    if (record -> event.pressed) {
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_OUT_IN); //set mode
      layer_move(0);
    } else {}
    return false;


  default:
    return true; //Process all other keycodes normally
  }
}


void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

//layer indication

// https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix

//layer 0 = base layer
/*
void rgb_matrix_indicators_kb(void) {
    rgb_matrix_set_color(index, red, green, blue);
}
*/

//layer 1 = CAPS layer = Standard functions = Green (0, 255, 0)

//layer 2 = RALT layer = Macro functions = Yellow (255, 255, 0)

//layer 3 = Fn layer = CPU system functions, Function keys = Orange (250, 100, 0)

//layer 4 = APP layer = Keyboard functions = Red (255, 0, 0)

//layer 5 = RCTRL layer = RGB keyboard functions = Cyan (0, 190, 255)

//layer 6 = RGB Selector = rotating rainbow

void rgb_matrix_indicators_user(void) {

  uint8_t layer = biton32(layer_state);

  switch (layer) {

  case 0:
    // rgb_matrix_set_color_all(0, 0, 255); //Light up all the keys in blue
    break;

  case 1:
    // rgb_matrix_set_color_all(3, 113, 255);

    // rgb_matrix_set_color_all(0, 0, 0); // rest of keys blank/black
    // rgb_matrix_set_color(0, 250, 100, 0); // esc for ctrl alt del | orange
    // rgb_matrix_set_color(1, 3, 200, 0); // F1 for JAN | yosemite green
    // rgb_matrix_set_color(2, 255, 0, 0); // F2 for FEB | red
    // rgb_matrix_set_color(3, 7, 145, 95); // F3 for MAR | teal, aurora borealis
    // rgb_matrix_set_color(4, 0, 190, 255); // F4 for APR | turquoise
    // rgb_matrix_set_color(5, 3, 113, 255); // F5 for MAY | horizon blue
    // rgb_matrix_set_color(6, 10, 31, 255); // F6 for JUN | atlantic blue
    // rgb_matrix_set_color(7, 10, 25, 220); // F7 for JUL | DC Supershow blue
    // rgb_matrix_set_color(8, 255, 193, 3); // F8 for AUG | apache sunset
    // rgb_matrix_set_color(9, 255, 150, 3); // F9 for SEP | mandarin orange
    // rgb_matrix_set_color(10, 154, 110, 15); // F10 for OCT | autumn oak
    // rgb_matrix_set_color(11, 154, 20, 0); // F11 for NOV | oxblood
    // rgb_matrix_set_color(12, 69, 102, 37); // F12 for DEC | olivine
    // rgb_matrix_set_color(16, 0, 190, 255); // ` for RGB TOG | cyan
    // rgb_matrix_set_color(17, 255, 0, 0); // 1 for keyboard | red
    // rgb_matrix_set_color(18, 255, 0, 0); // 2 for keyboard | red
    // rgb_matrix_set_color(19, 255, 0, 0); // 3 for keyboard | red
    // rgb_matrix_set_color(34, 0, 190, 255); // q for RGB | cyan
    // rgb_matrix_set_color(35, 0, 190, 255); // w for RGB | cyan
    // rgb_matrix_set_color(36, 0, 190, 255); // e for RGB | cyan
    // rgb_matrix_set_color(51, 0, 190, 255); // a for RGB | cyan
    // rgb_matrix_set_color(52, 0, 190, 255); // s for RGB | cyan
    // rgb_matrix_set_color(53, 0, 190, 255); // d for RGB | cyan
    // rgb_matrix_set_color(44, 0, 190, 255); // [ for RGB | cyan
    // rgb_matrix_set_color(45, 0, 190, 255); // ] for RGB | cyan
    // rgb_matrix_set_color(29, 255, 0, 0); // backspace for MD_LOAD | red
    // rgb_matrix_set_color(39, 255, 0, 0); // y for keyboard | red
    // rgb_matrix_set_color(40, 255, 0, 0); // u for keyboard | red
    // rgb_matrix_set_color(69, 255, 0, 0); // n for keyboard | red
    // rgb_matrix_set_color(71, 0, 190, 255); // < for RGB | cyan
    // rgb_matrix_set_color(72, 0, 190, 255); // > for RGB | cyan
    // rgb_matrix_set_color(13, 0, 255, 0); // print for mute | green
    // rgb_matrix_set_color(30, 0, 255, 0); // insert for playback | green
    // rgb_matrix_set_color(31, 0, 255, 0); // home for playback | green
    // rgb_matrix_set_color(32, 0, 255, 0); // pgup for playback | green
    // rgb_matrix_set_color(47, 0, 255, 0); // del for playback | green
    // rgb_matrix_set_color(48, 0, 255, 0); // end for playback | green
    // rgb_matrix_set_color(49, 0, 255, 0); // pgdn for playback | green
    // rgb_matrix_set_color(20, 0, 0, 255); // for BLUE
    // rgb_matrix_set_color(21, 250, 100, 0); // for TNOB
    // rgb_matrix_set_color(22, 0, 100, 250); // for TNBO
    // rgb_matrix_set_color(23, 250, 100, 0); // for ORNG
    // rgb_matrix_set_color(24, 0, 100, 250); // for CYAN
    // rgb_matrix_set_color(25, 0, 255, 0); // for GRNP
    // rgb_matrix_set_color(26, 255, 20, 147); // for MIAMI
    // rgb_matrix_set_color(27, 1, 50, 32); // for XMAS
    // rgb_matrix_set_color(28, 139, 0, 0); // for SAMX
    // rgb_matrix_set_color(67, 0, 190, 255); // v for RGB palette layer 2

    rgb_matrix_set_color(49, 3, 200, 0); // yosemite green
    rgb_matrix_set_color(50, 3, 200, 0); // yosemite green
    rgb_matrix_set_color(51, 3, 200, 0); // yosemite green
    rgb_matrix_set_color(52, 3, 200, 0); // yosemite green
    rgb_matrix_set_color(53, 3, 200, 0); // yosemite green
    rgb_matrix_set_color(54, 3, 200, 0); // yosemite green

    break;

  case 2:
    rgb_matrix_set_color_all(0, 190, 255);


    // rgb_matrix_set_color_all(0, 0, 0); // rest of keys blank/black
    // rgb_matrix_set_color(7, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(8, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(9, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(10, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(11, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(22, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(23, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(24, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(25, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(37, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(38, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(39, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(40, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(51, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(52, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(53, 255, 255, 0); // YLLW43 true yellow

    // rgb_matrix_set_color(56, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(64, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(65, 255, 255, 0); // YLLW43 true yellow
    // rgb_matrix_set_color(66, 255, 255, 0); // YLLW43 true yellow



    // rgb_matrix_set_color(17, 255, 0, 0); // RED0 true red, 1
    // rgb_matrix_set_color(34, 255, 68, 0); // RED5, Q
    // rgb_matrix_set_color(51, 255, 111, 0); // RED10, A
    // rgb_matrix_set_color(64, 255, 179, 0); // RED15 red orange, Z
    // rgb_matrix_set_color(18, 204, 204, 0); // ORNG21 true orange, 2
    // rgb_matrix_set_color(35, 255, 205, 0); // ORNG26, W
    // rgb_matrix_set_color(52, 255, 217, 0); // ORNG31, S
    // rgb_matrix_set_color(65, 255, 230, 0); // ORNG36, X
    // rgb_matrix_set_color(19, 255, 255, 0); // YLLW43 true yellow, 3
    // rgb_matrix_set_color(36, 196, 255, 0); // YLLW53, E
    // rgb_matrix_set_color(53, 154, 255, 0); // YLLW63, D
    // rgb_matrix_set_color(66, 111, 255, 0); // YLLW73, C
    // rgb_matrix_set_color(20, 0, 255, 0); // GRN85 true green, 4
    // rgb_matrix_set_color(37, 0, 255, 50); // GRN95, R
    // rgb_matrix_set_color(54, 0, 255, 75); // GRN105, F
    // rgb_matrix_set_color(67, 0, 255, 120); // GRN115, V
    // rgb_matrix_set_color(21, 0, 255, 255); // CYAN127 true cyan, 5
    // rgb_matrix_set_color(38, 0, 213, 255); // CYAN132, T
    // rgb_matrix_set_color(55, 0, 196, 255); // CYAN137, G
    // rgb_matrix_set_color(68, 0, 154, 255); // CYAN142, B
    // rgb_matrix_set_color(22, 0, 128, 255); // AZRE148 true azure, 6
    // rgb_matrix_set_color(39, 0, 102, 255); // AZRE153, Y
    // rgb_matrix_set_color(56, 0, 77, 255); // AZRE158, H
    // rgb_matrix_set_color(69, 0, 60, 255); // AZRE163, N
    // rgb_matrix_set_color(23, 0, 0, 255); // BLUE169 true blue, 7
    // rgb_matrix_set_color(40, 43, 0, 255); // BLUE172, U
    // rgb_matrix_set_color(57, 60, 0, 255); // BLUE175, J
    // rgb_matrix_set_color(70, 77, 0, 255); // BLUE178, M
    // rgb_matrix_set_color(24, 127, 0, 255); // VILT180 true violet, 8
    // rgb_matrix_set_color(41, 171, 0, 255); // VILT185, I
    // rgb_matrix_set_color(58, 200, 0, 255); // VILT190, K
    // rgb_matrix_set_color(71, 215, 0, 255); // VILT195, <
    // rgb_matrix_set_color(25, 255, 0, 255); // MGTA201 true magenta, 9
    // rgb_matrix_set_color(42, 255, 0, 240); // MGTA206, O
    // rgb_matrix_set_color(59, 255, 0, 220); // MGTA211, L
    // rgb_matrix_set_color(72, 255, 0, 200); // MGTA217, >
    // rgb_matrix_set_color(26, 255, 0, 127); // ROSE222 true rose, 0
    // rgb_matrix_set_color(43, 255, 0, 111); // ROSE230, P
    // rgb_matrix_set_color(60, 255, 0, 70); // ROSE238, :
    // rgb_matrix_set_color(73, 255, 0, 26); // ROSE245, ?
    // rgb_matrix_set_color(0, 255, 0, 0); // ESC red

    break;
  }
}