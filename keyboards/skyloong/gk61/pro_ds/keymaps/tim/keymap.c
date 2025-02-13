// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// Copyright 2024 Tim Dodge
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_us_international.h"
#include "sendstring_us_international.h"

#define WIN_MOD_INDEX 16

enum layer_names {
    _WIN,
    _WIN_INDEX,
    _SPCFN,
};

enum tap_hold_keys {
    _DN_MU // Tap--KC_DOWN  and  Hold--KC_APP
};

enum custom_keycodes {
  CK_SELWORD = SAFE_RANGE
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_UP):
            return TAPPING_TERM - 80; // right shift hold time less than default tapping term 80ms
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   |Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   |Sft|   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│GUI│Alt│   │   │Spc│   │   |   |Alt│App│App│   │Ctl|
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_WIN] = LAYOUT_60_ansi(
        QK_GESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,       KC_EQL,     KC_BSPC,
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,       KC_RBRC,    KC_BSLS,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,                   KC_ENT,
        OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  RSFT_T(KC_UP),
        KC_LCTL,       KC_LGUI, KC_LALT, LT(_SPCFN, KC_SPC),  KC_RCTL,   LT(_WIN_INDEX, KC_LEFT),  TD(_DN_MU), RALT_T(KC_RIGHT)
    ),

    [_WIN_INDEX] =  LAYOUT_60_ansi(
        KC_GRV ,    KC_F1,    KC_F2,      KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        _______,  _______,  _______,    _______,  _______,  _______,     _______,  _______,  _______,  _______,  RGB_M_P,  RGB_RMOD, RGB_RMOD, RGB_TOG,
        _______,  _______,  _______,    _______,  _______,  _______,     _______,  _______,  RGB_SAD,  RGB_SAI,  RGB_SPD,  RGB_SPI,            _______,
        _______,  _______,  _______,    _______,  _______,  _______,     RGB_HUD,  RGB_HUI,  RGB_VAD,  RGB_VAI,  CK_SELWORD,              _______,
        _______,  _______,  _______,              _______,  _______,                         _______,  _______,  _______
    ),

    [_SPCFN] = LAYOUT_60_ansi(
        KC_GRV ,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,
        _______,  _______,  _______,   KC_ESC,  _______,  _______,  KC_PGUP,  KC_HOME,    KC_UP,   KC_END,  KC_PSCR,  KC_SCRL, KC_PAUS,  KC_INS,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,  _______,          _______,
        _______,  _______,  _______,  _______,  _______,   KC_SPC,  _______,  _______,   KC_GRV,  KC_TILD,   CK_SELWORD,           KC_PGUP,
        _______,  _______,  _______,            _______,                      _______,  KC_HOME,  KC_PGDN,           KC_END
    )
};

const key_override_t word_left_override = ko_make_basic(MOD_BIT(KC_RCTL), LT(_WIN_INDEX, KC_LEFT), RCTL(KC_LEFT));
const key_override_t word_right_override = ko_make_basic(MOD_BIT(KC_RCTL), RALT_T(KC_RIGHT), RCTL(KC_RIGHT));
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &word_left_override,
    &word_right_override,
    &delete_key_override
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
    {                                                                               \
        .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
    }

tap_dance_action_t tap_dance_actions[] = {
    [_DN_MU] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOWN, KC_APP),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {

        case TD(_DN_MU):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;

        case CK_SELWORD:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
            }
            return false;

        default:
            return true;
    }
}

