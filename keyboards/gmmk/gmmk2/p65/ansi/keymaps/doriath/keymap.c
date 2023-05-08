#include QMK_KEYBOARD_H
// #include "print.h"

enum ctrl_keycodes {
  MD_BOOT = SAFE_RANGE,               //Restart into bootloader after hold timeout
    // U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    // U_T_AGCR,              //USB Toggle Automatic GCR control
    // DBG_TOG,               //DEBUG Toggle On / Off
    // DBG_MTRX,              //DEBUG Toggle Matrix Prints
    // DBG_KBD,               //DEBUG Toggle Keyboard Prints
    // DBG_MOU,               //DEBUG Toggle Mouse Prints
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
  CYCLE_lra,
  CYCLE_uda,
  RAIN_mcha,
  CYCLE_oia,
  MD_GUITOG,
  MD_LCAP,
  MD_PSPD // DEBUG print animation speed to console
};


/* 
 * GMMK 2 Compact ANSI
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,     // 00-14
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_HOME,    // 15-29
  KC_F13,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_END,     // 30-43
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,    // 44-57
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RCTL,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT),   // 58-66

[1] = LAYOUT(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  KC_INS,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  MD_BOOT,  _______,
  KC_CAPS,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,            RGB_VAI,  KC_PGUP,
  _______,  GUI_TOG,  _______,                                _______,                                TG(2),    _______,  RGB_RMOD, RGB_VAD,  RGB_MOD),

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

// static bool mod_state_GUI_TOG = false;
// static bool mod_state_KC_LCAP = false;



bool caps_lock_on = false;
static bool gui_lock_on = false;

// void check_caps_lock_status(void) {
//     if (caps_lock_on) {
//         unregister_code(KC_CAPS);
//     } else {
//         register_code(KC_CAPS);
//     }
// }



#define IDLE_TIMEOUT_MS 5000  // Idle timeout in milliseconds.
static uint16_t idle_timer = 0;

void matrix_scan_user(void) {
  if (idle_timer && timer_expired(timer_read(), idle_timer)) {
    // If execution reaches here, the keyboard has gone idle.
    if (biton32(layer_state) == 2) {
      layer_move(0);
    }
    idle_timer = 0;
  }

  if (caps_lock_on) {
    rgb_matrix_set_color(30, 3, 200, 0); // yosemite green
    rgb_matrix_set_color(44, 3, 200, 0); // yosemite green
  }


  if (gui_lock_on) {
    rgb_matrix_set_color(59, 3, 200, 0); // yosemite green
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // On every key event, set idle_timer to expire after IDLE_TIMEOUT_MS.
  // We use idle_timer == 0 to indicate that the timer is inactive, so
  // the value is bitwise or'd with 1 to ensure it is nonzero.
  idle_timer = (record->event.time + IDLE_TIMEOUT_MS) | 1;

  static uint32_t key_timer;

  switch (keycode) {
    // case MD_PSPD:
    //   if (record->event.pressed) {
    //     uprintf("speed: %d\n", rgb_matrix_get_speed());
    //   }
    //   return false;

    case KC_CAPS:
      if (record->event.pressed) {
        // if (caps_lock_on) {
        //   unregister_code(KC_CAPS);
        // } else {
        //   register_code(KC_CAPS);
        // }
        caps_lock_on = !caps_lock_on;
      }
      return true;
  // case MD_LCAP:
  //   if (record->event.pressed) {
  //     caps_lock_on = !caps_lock_on;
  //   }
  //   return false;


  // case KC_LGUI:
  //   if (record->event.pressed) {
  //     if (gui_lock_on) {
  //       unregister_code(KC_LGUI);
  //       unregister_mods(MOD_MASK_GUI);
  //     } else {
  //       register_code(KC_LGUI);
  //     }
  //   }
  //   return false;    
  // case MD_GUITOG:
  //   if (record->event.pressed) {
  //     gui_lock_on = !gui_lock_on;
  //     unregister_mods(MOD_MASK_GUI);
  //   }
  //   return false;
    case GUI_TOG:
    if (record->event.pressed) {
      gui_lock_on = !gui_lock_on;
    }
    return true;



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

  // case MD_LCAP:
  //   if (record -> event.pressed) {
  //       if (mod_state_KC_LCAP) {
  //         mod_state_KC_LCAP = false;
  //         rgb_matrix_set_color(30, 0, 0, 0); // off
  //         register_code(KC_LCAP);
  //       } else {
  //         mod_state_KC_LCAP = true;
  //         rgb_matrix_set_color(30, 3, 200, 0); // yosemite green
  //         unregister_code(KC_LCAP);
  //       }
  //   }
  //   return false;
  // case MD_GUITOG:
  //   if (record -> event.pressed) {
  //       if (mod_state_GUI_TOG) {
  //         mod_state_GUI_TOG = false;
  //         rgb_matrix_set_color(30, 0, 0, 0); // off
  //         register_code(GUI_TOG);
  //       } else {
  //         mod_state_GUI_TOG = true;
  //         rgb_matrix_set_color(30, 255, 0, 0); // red
  //         unregister_code(GUI_TOG);
  //     }
  //   }
  //   return false;



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
    // rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    // rgb_matrix_set_suspend_state(false);
    // clear_mods();
}


void keyboard_post_init_user(void) {
  rgb_matrix_set_flags(LED_FLAG_ALL);
  rgb_matrix_enable_noeeprom();
  rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
  rgb_matrix_set_speed(16);
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
  // don't apply layer colors when only UNDERGLOW is enabled
  if (rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
    return;
  }

  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case 0:
      break;

    case 1:
      // rgb_matrix_set_color_all(3, 113, 255);
      rgb_matrix_set_color(49, 3, 200, 0); // yosemite green
      rgb_matrix_set_color(50, 3, 200, 0); // yosemite green
      rgb_matrix_set_color(51, 3, 200, 0); // yosemite green
      rgb_matrix_set_color(52, 3, 200, 0); // yosemite green
      rgb_matrix_set_color(53, 3, 200, 0); // yosemite green
      rgb_matrix_set_color(54, 3, 200, 0); // yosemite green

      break;

    case 2:
      rgb_matrix_set_color_all(0, 190, 255);
      break;
  }
}
