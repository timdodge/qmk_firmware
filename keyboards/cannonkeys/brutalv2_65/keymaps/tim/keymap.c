/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

enum layer_names {
    _BASE,
    _SPCFN,
};

enum custom_keycodes { CK_SELWD = SAFE_RANGE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT_65_iso_blocker(
		QK_GESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS, KC_EQL,      KC_BSPC,  KC_DEL,
 		 KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_LBRC, KC_RBRC,              KC_PGUP,
		KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT, KC_NUHS,      KC_ENT, KC_PGDN,
  OSM(MOD_LSFT),  KC_NUBS,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH, OSM(MOD_RSFT), KC_UP,  KC_INS,
		KC_LCTL,  KC_LGUI,  KC_LALT,                                 KC_SPC,                   MO(_SPCFN),  KC_RCTL,           KC_LEFT,     KC_DOWN, KC_RGHT
    ),

    [_SPCFN] = LAYOUT_65_iso_blocker(
        KC_GRV ,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,  KC_F12, _______, _______,
        _______,  _______,  _______,   KC_ESC,  _______,  _______,  KC_PGUP,  KC_HOME,    KC_UP,   KC_END,  KC_PSCR,  KC_SCRL, KC_PAUS,          _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_PGDN,  KC_LEFT,  KC_DOWN, KC_RIGHT,  _______,  _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,   KC_SPC,  _______,  _______,   KC_GRV,  KC_TILD, CK_SELWD, _______, KC_PGUP, _______,
        _______,  _______,  _______,                                _______,                      _______,  _______,           KC_HOME, KC_PGDN,  KC_END
    ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case CK_SELWD:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
            }
            return false;

        default:
            return true;
    }
}
