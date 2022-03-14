/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_MIRYOKU = 0,
    LAYER_MIR_SYM,
    LAYER_MIR_NAV,
    LAYER_MIR_NUM,
    LAYER_MIR_MOUSE,
    
    // Media controls on nav layer outer columns
    //LAYER_MIR_MEDIA,
    // Function keys on nav layer top row
    //LAYER_MIR_FN,
    //LAYER_POINTER = LAYER_MIR_MOUSE,
};
#define LAYER_POINTER LAYER_MIR_MOUSE

/** \brief Automatically enable sniping-mode on the pointer layer. */
//#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif      // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define REDO LCTL(KC_Y)
#define ALT_APP LALT_T(KC_APP)
#define CTL_ESC LCTL_T(KC_ESC)

#define LGUI_A LGUI_T(KC_A)
#define LALT_S LALT_T(KC_S)
#define LCTL_D LCTL_T(KC_D)
#define LSFT_F LSFT_T(KC_F)

#define LGUI_SCN LGUI_T(KC_SCLN)
#define LALT_L LALT_T(KC_L)
#define LCTL_K LCTL_T(KC_K)
#define LSFT_J LSFT_T(KC_J)

#define NAV_BS LT(LAYER_MIR_NAV, KC_BSPC)
#define MOU_TAB LT(LAYER_MIR_MOUSE, KC_TAB)
#define NUM_SPC LT(LAYER_MIR_NUM, KC_SPC)
#define SYM_ENT LT(LAYER_MIR_SYM, KC_ENT)

enum userspace_keycodes {
#ifndef NO_CHARYBDIS_KEYCODES
  POINTER_OFF = CHARYBDIS_SAFE_RANGE,
#else
  POINTER_OFF = SAFE_RANGE,
#endif // !NO_CHARYBDIS_KEYCODES

  // ... more keys
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_MIRYOKU] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_EQL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LBRC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LGUI,    LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G,       KC_H,    LSFT_J,  LCTL_K,  LALT_L,  LGUI_SCN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  NAV_BS,  MOU_TAB, ALT_APP,    SYM_ENT, NUM_SPC,
                                           KC_ESC,  CTL_ESC,    KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MIR_SYM] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_DQUO, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,    _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,    _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_LPRN, KC_UNDS, _______,    _______, _______,
                                           KC_RPRN, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),


  [LAYER_MIR_NAV] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MNXT, _______, _______, _______, _______, _______,    KC_INS, KC_HOME,   KC_UP,   KC_END,   KC_PGUP, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPLY, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,    KC_CAPS, KC_LEFT,   KC_DOWN, KC_RIGHT, KC_PGDN, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPRV, _______, _______, _______, _______, _______,    REDO,    PASTE,     COPY,    CUT,      UNDO,    KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MIR_NUM] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_LBRC,   KC_P7, KC_P8,    KC_P9,  KC_RBRC,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_PPLS,   KC_P4, KC_P5,    KC_P6,  KC_EQL,     _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_GRV,    KC_P1, KC_P2,    KC_P3,  KC_PSLS,    _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_P0,  KC_PMNS,  _______,    _______, _______,
                                          KC_PDOT, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MIR_MOUSE] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       RESET,   EEP_RST, _______, _______, _______, _______,    _______, _______, _______, _______,  EEP_RST, RESET,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    S_D_MOD, DPI_MOD, DRG_TOG, LGUI(KC_TAB), KC_BTN5, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,    SNP_TOG, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN4, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    REDO,    PASTE,     COPY,    CUT,      UNDO, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || 
        abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD ||
        // Drag-scrolling changes mouse x/y into mouse h/v
        (charybdis_get_pointer_dragscroll_enabled() && (mouse_report.h != 0 || mouse_report.v != 0))
     ) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif  // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_kb(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
#        endif  // RGB_MATRIX_ENABLE
    }
    matrix_scan_user();
}
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif  // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif      // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb_red();
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode)
    {
    case POINTER_OFF:
      if (record->event.pressed) {
           layer_off(LAYER_POINTER);
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
           auto_pointer_layer_timer = 0;
#     endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
      }
      return false;
    }
    // continue processing key
    return true;
}
