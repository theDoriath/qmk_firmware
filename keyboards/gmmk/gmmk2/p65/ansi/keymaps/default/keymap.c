#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.


enum custom_keycodes {
    COPY = 0,
	PASTE,
	CUT,
	UNDO
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case COPY:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
             SEND_STRING(SS_LCTL("ac"));
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case PASTE:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LCTL("V")); 
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case CUT:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
           SEND_STRING(SS_LCTL("X")); 
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case UNDO:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LCTL("Z")); 
        } else {
           
        }
        break;
	}
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, RGB_TOG,
KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_DEL,
KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

[1] = LAYOUT(
KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, RGB_MOD,
_______, _______, _______, KC_BSPC, _______, _______, _______, _______, _______, _______, KC_CAPS, RGB_HUD, RGB_HUI, _______, RGB_VAI,
_______, KC_WREF, _______, KC_DEL, RGB_SPD, RGB_SPI, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, _______, RGB_VAD,
_______, _______, UNDO, CUT, COPY, PASTE, RGB_VAD, RGB_VAI, KC_HOME, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_PGUP, KC_INS,
_______, _______, _______, RESET, _______, _______, KC_HOME, KC_PGDN, KC_END),

[2] = LAYOUT(
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______, _______, _______)
};