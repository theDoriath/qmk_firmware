/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.€
// The underscores don't mean anything - you can have a layer called STUFF or any other name.


enum custom_keycodes {
    EURO = 0,
	TD_SHIFT
};


void leaderkey(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >= 2) {
        qk_leader_start();
    }
	else {
		SEND_STRING(SS_DOWN(X_LSFT));
	}

}	
void leaderkeydone(qk_tap_dance_state_t *state, void *user_data) {

		SEND_STRING(SS_UP(X_LSFT));
	

}
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_SHIFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, leaderkey, leaderkeydone)
// Other declarations would go here, separated by commas, if you have them
};
		

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case EURO:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8)SS_UP(X_LALT));
        } else {
            // when keycode QMKBEST is released
        }
        break;
	}
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
  TO(1)  ,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,			  KC_PGDN,
  TD(TD_SHIFT),  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  			KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT),

[1] = LAYOUT(
  KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,  KC_INS,
  TO(2)  ,  DEBUG  ,  KC_CALCULATOR,  _______,  QK_CLEAR_EEPROM,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  _______,  _______,
  TO(0)  ,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,			  _______,
  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  _______,  KC_MUTE,  KC_VOLU,  KC_VOLD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  			RGB_VAI,  KC_HOME,
  _______,  _______,  _______,                                RESET,                                  _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_MOD),


[2] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  DYN_REC_START1,  DYN_REC_START2,  DYN_REC_STOP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  DYN_MACRO_PLAY1,  DYN_MACRO_PLAY2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,			  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  			_______,  _______,
  _______,  _______,  _______,                                _______,                                _______,   TO(3),  _______,  _______,  _______),

[3] = LAYOUT(
  _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_0,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  EURO,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,			  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  			_______,  _______,
  _______,  _______,  _______,                                _______,                                _______,  TO(0),  _______,  _______,  _______),
};






void keyboard_post_init_user(void) {
  //Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  //debug_keyboard=true;
 // debug_mouse=true;
 //rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
 //rgblight_set_speed(50);
}


LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_R) {
      // Anything you can do in a macro.
      SEND_STRING("Robin is the best!");
    }
	SEQ_ONE_KEY(KC_E) {
		SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8)SS_UP(X_LALT));
	}
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(30, 255,255,255); //capslock key
    }
	
	switch(get_highest_layer(layer_state)){  // special handling per layer
            case 1:  //layer one
				rgb_matrix_set_color(0, 255, 255, 255); 
				rgb_matrix_set_color(1, 255, 255, 255);
				rgb_matrix_set_color(2, 255, 255, 255);
				rgb_matrix_set_color(3, 255, 255, 255);
				rgb_matrix_set_color(4, 255, 255, 255);
				rgb_matrix_set_color(5, 255, 255, 255);
				rgb_matrix_set_color(6, 255, 255, 255);
				rgb_matrix_set_color(7, 255, 255, 255);
				rgb_matrix_set_color(8, 255, 255, 255);
				rgb_matrix_set_color(9, 255, 255, 255);
				rgb_matrix_set_color(10, 255, 255, 255);
				rgb_matrix_set_color(11, 255, 255, 255);
				rgb_matrix_set_color(12, 255, 255, 255);
				rgb_matrix_set_color(14, 255, 255, 255);
				rgb_matrix_set_color(15, 255, 255, 255); 
				rgb_matrix_set_color(16, 255, 255, 255);
				rgb_matrix_set_color(17, 255, 255, 255);
				rgb_matrix_set_color(25, 255, 255, 255);
				rgb_matrix_set_color(26, 255, 255, 255);
				rgb_matrix_set_color(27, 255, 255, 255);
				rgb_matrix_set_color(45, 255, 255, 255);
				rgb_matrix_set_color(46, 255, 255, 255);
				rgb_matrix_set_color(47, 255, 255, 255);
				rgb_matrix_set_color(48, 255, 255, 255);
				rgb_matrix_set_color(49, 255, 255, 255);
				rgb_matrix_set_color(50, 255, 255, 255);
				rgb_matrix_set_color(51, 255, 255, 255);
				rgb_matrix_set_color(52, 255, 255, 255);
				rgb_matrix_set_color(53, 255, 255, 255);
				rgb_matrix_set_color(54, 255, 255, 255);
				rgb_matrix_set_color(56, 255, 255, 255);
				rgb_matrix_set_color(57, 255, 255, 255);
				rgb_matrix_set_color(64, 255, 255, 255);
				rgb_matrix_set_color(65, 255, 255, 255);
				rgb_matrix_set_color(66, 255, 255, 255);
				break;
			case 2:
				rgb_matrix_set_color(0, 255, 0, 0);
				rgb_matrix_set_color(16, 255, 0, 0);
				rgb_matrix_set_color(17, 255, 0, 0);
				rgb_matrix_set_color(18, 255, 255, 0);
				rgb_matrix_set_color(31, 0, 255, 0);
				rgb_matrix_set_color(32, 0, 255, 0);
				break;
			case 3:
				rgb_matrix_set_color(0, 0, 0, 255);
				rgb_matrix_set_color(18, 255, 255, 0);
				break;
            default:
                break;
            break;
}
}