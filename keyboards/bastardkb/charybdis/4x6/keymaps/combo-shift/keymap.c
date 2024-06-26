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
    LAYER_VANILLA = 0,
    LAYER_MIRYOKU,
    LAYER_COMBO,
    LAYER_THE,
    LAYER_THE_SFT,
    LAYER_MIR_SYM,
    LAYER_MIR_NAV,
    LAYER_MIR_NUM,
    LAYER_MIR_MOUSE,
    
    // Media controls on nav layer outer columns
    //LAYER_MIR_MEDIA,
    // Function keys on nav layer top row
    LAYER_MIR_FN,
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
#define FUN_DEL LT(LAYER_MIR_FN, KC_DEL)

#define K_THSFT MO(LAYER_THE_SFT)

enum userspace_keycodes {
#ifndef NO_CHARYBDIS_KEYCODES
  PNTR_OFF = CHARYBDIS_SAFE_RANGE,
#else
  PNTR_OFF = SAFE_RANGE,
#endif // !NO_CHARYBDIS_KEYCODES

  // ... more keys
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_VANILLA] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_EQL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TO(LAYER_MIRYOKU),   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LGUI,    KC_A,  KC_S,  KC_D,  KC_F,  KC_G,       KC_H,    KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  NAV_BS,  KC_TAB,  ALT_APP,    SYM_ENT, NUM_SPC,
                                           KC_ESC,  CTL_ESC,    FUN_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MIRYOKU] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_EQL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TO(LAYER_COMBO),   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LGUI,    LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G,       KC_H,    LSFT_J,  LCTL_K,  LALT_L,  LGUI_SCN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  NAV_BS,  KC_TAB,  ALT_APP,    SYM_ENT, NUM_SPC,
                                           KC_ESC,  CTL_ESC,    FUN_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_COMBO] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_EQL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TO(LAYER_THE),   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LGUI,    KC_A,  KC_S,  KC_D,  KC_F,  KC_G,       KC_H,    KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  NAV_BS,  KC_TAB,  ALT_APP,    SYM_ENT, NUM_SPC,
                                           KC_ESC,  CTL_ESC,    FUN_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_THE] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TO(LAYER_VANILLA),   KC_K,    KC_M,    KC_L,    KC_U,  KC_QUES,      KC_V,    KC_D,    KC_R,    KC_QUOT, KC_Q,  _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,   KC_A,    KC_T,    KC_H,    KC_E,  KC_DOT,       KC_C,    KC_S,    KC_N,    KC_O,    KC_I,  _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       K_THSFT,   KC_Z,    KC_P,    KC_F,    KC_J,  KC_COMM,      KC_B,    KC_G,    KC_W,    KC_X,    KC_Y,  K_THSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_THE_SFT] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       S(KC_EQL), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),    S(KC_6), S(KC_7), S(KC_8), S(KC_9),    S(KC_0), S(KC_MINS),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, S(KC_K), S(KC_M), S(KC_L), S(KC_U), KC_EXLM,    S(KC_V), S(KC_D), S(KC_R), S(KC_QUOT), S(KC_Q),  S(KC_BSLS),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, S(KC_A), S(KC_T), S(KC_H), S(KC_E), KC_COLN,    S(KC_C), S(KC_S), S(KC_N), S(KC_O),    S(KC_I),  _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, S(KC_Z), S(KC_P), S(KC_F), S(KC_J), KC_SCLN,    S(KC_B), S(KC_G), S(KC_W), S(KC_X),    S(KC_Y),  _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MIR_SYM] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
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
                                  _______, _______, _______,    KC_ENT, KC_SPC,
                                           _______, _______,    KC_DEL
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
       PNTR_OFF,_______, _______, _______, _______, _______,    _______, _______, _______, _______,  EEP_RST, RESET,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, LGUI(KC_TAB), DRG_TOG, SNP_TOG,    SNP_TOG, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    REDO,    PASTE,     COPY,    CUT,      UNDO, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN1, KC_BTN2, KC_BTN5,    PNTR_OFF, PNTR_OFF,
                                           KC_BTN3, KC_BTN4,    PNTR_OFF
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

   [LAYER_MIR_FN] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_F12,    KC_F7,   KC_F8,   KC_F9,  KC_PSCR,   _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_F11,    KC_F4,   KC_F5,   KC_F6,  KC_SCRL,   _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_F10,    KC_F1,   KC_F2,   KC_F3,  KC_PAUS,   _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BSPC, KC_TAB,  _______,    _______, _______,
                                           KC_APP,  _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

};
// clang-format on

enum combo_events {
     F_6,
     F_7,
     F_8,
     F_9,
     F_0,

     FY,
     FU,
     FI,
     FO,
     FP,
     
     FH,
     FJ,
     FK,
     FL,
     FSCN,

     FN,
     FM,
     FCOMM,
     FDOT,
     FSLSH,



     J_1,
     J_2,
     J_3,
     J_4,
     J_5,

     JQ,
     JW,
     JE,
     JR,
     JT,

     JA,
     JS,
     JD,
     JF,
     JG,

     JZ,
     JX,
     JC,
     JV,
     JB,

     W1,

     COMBO_LENGTH,
};

uint16_t COMBO_LEN = COMBO_LENGTH;

// const uint16_t PROGMEM f_6[] = {LSFT_F, KC_6, COMBO_END};
// const uint16_t PROGMEM f_7[] = {LSFT_F, KC_7, COMBO_END};
// const uint16_t PROGMEM f_8[] = {LSFT_F, KC_8, COMBO_END};
// const uint16_t PROGMEM f_9[] = {LSFT_F, KC_9, COMBO_END};
// const uint16_t PROGMEM f_0[] = {LSFT_F, KC_0, COMBO_END};


// const uint16_t PROGMEM fy[] = {LSFT_F, KC_Y, COMBO_END};
// const uint16_t PROGMEM fu[] = {LSFT_F, KC_U, COMBO_END};
// const uint16_t PROGMEM fi[] = {LSFT_F, KC_I, COMBO_END};
// const uint16_t PROGMEM fo[] = {LSFT_F, KC_O, COMBO_END};
// const uint16_t PROGMEM fp[] = {LSFT_F, KC_P, COMBO_END};

// const uint16_t PROGMEM fh[] = {LSFT_F, KC_H, COMBO_END};
// //const uint16_t PROGMEM fj[] = {LSFT_F, LSFT_J, COMBO_END};
// const uint16_t PROGMEM fk[] = {LSFT_F, LCTL_K, COMBO_END};
// const uint16_t PROGMEM fl[] = {LSFT_F, LALT_L, COMBO_END};
// const uint16_t PROGMEM fscn[] = {LSFT_F, LGUI_SCN, COMBO_END};

// const uint16_t PROGMEM fn[] = {LSFT_F, KC_N, COMBO_END};
// const uint16_t PROGMEM fm[] = {LSFT_F, KC_M, COMBO_END};
// const uint16_t PROGMEM fcomm[] = {LSFT_F, KC_COMM, COMBO_END};
// const uint16_t PROGMEM fdot[] = {LSFT_F, KC_DOT, COMBO_END};
// const uint16_t PROGMEM fslsh[] = {LSFT_F, KC_SLSH, COMBO_END};
const uint16_t PROGMEM f_6[] = {NAV_BS, KC_6, COMBO_END};
const uint16_t PROGMEM f_7[] = {NAV_BS, KC_7, COMBO_END};
const uint16_t PROGMEM f_8[] = {NAV_BS, KC_8, COMBO_END};
const uint16_t PROGMEM f_9[] = {NAV_BS, KC_9, COMBO_END};
const uint16_t PROGMEM f_0[] = {NAV_BS, KC_0, COMBO_END};


const uint16_t PROGMEM fy[] = {NAV_BS, KC_Y, COMBO_END};
const uint16_t PROGMEM fu[] = {NAV_BS, KC_U, COMBO_END};
const uint16_t PROGMEM fi[] = {NAV_BS, KC_I, COMBO_END};
const uint16_t PROGMEM fo[] = {NAV_BS, KC_O, COMBO_END};
const uint16_t PROGMEM fp[] = {NAV_BS, KC_P, COMBO_END};

const uint16_t PROGMEM fh[] = {NAV_BS, KC_H, COMBO_END};
const uint16_t PROGMEM fj[] = {NAV_BS, KC_J, COMBO_END};
const uint16_t PROGMEM fk[] = {NAV_BS, KC_K, COMBO_END};
const uint16_t PROGMEM fl[] = {NAV_BS, KC_L, COMBO_END};
const uint16_t PROGMEM fscn[] = {NAV_BS, KC_SCLN, COMBO_END};

const uint16_t PROGMEM fn[] = {NAV_BS, KC_N, COMBO_END};
const uint16_t PROGMEM fm[] = {NAV_BS, KC_M, COMBO_END};
const uint16_t PROGMEM fcomm[] = {NAV_BS, KC_COMM, COMBO_END};
const uint16_t PROGMEM fdot[] = {NAV_BS, KC_DOT, COMBO_END};
const uint16_t PROGMEM fslsh[] = {NAV_BS, KC_SLSH, COMBO_END};



// const uint16_t PROGMEM j_1[] = {LSFT_J, KC_1, COMBO_END};
// const uint16_t PROGMEM j_2[] = {LSFT_J, KC_2, COMBO_END};
// const uint16_t PROGMEM j_3[] = {LSFT_J, KC_3, COMBO_END};
// const uint16_t PROGMEM j_4[] = {LSFT_J, KC_4, COMBO_END};
// const uint16_t PROGMEM j_5[] = {LSFT_J, KC_5, COMBO_END};

// const uint16_t PROGMEM jq[] = {LSFT_J, KC_Q, COMBO_END};
// const uint16_t PROGMEM jw[] = {LSFT_J, KC_W, COMBO_END};
// const uint16_t PROGMEM je[] = {LSFT_J, KC_E, COMBO_END};
// const uint16_t PROGMEM jr[] = {LSFT_J, KC_R, COMBO_END};
// const uint16_t PROGMEM jt[] = {LSFT_J, KC_T, COMBO_END};

// const uint16_t PROGMEM ja[] = {LSFT_J, LGUI_A, COMBO_END};
// const uint16_t PROGMEM js[] = {LSFT_J, LALT_S, COMBO_END};
// const uint16_t PROGMEM jd[] = {LSFT_J, LCTL_D, COMBO_END};
// //const uint16_t PROGMEM jf[] = {LSFT_J, LSFT_F, COMBO_END};
// const uint16_t PROGMEM jg[] = {LSFT_J, KC_G, COMBO_END};

// const uint16_t PROGMEM jz[] = {LSFT_J, KC_Z, COMBO_END};
// const uint16_t PROGMEM jx[] = {LSFT_J, KC_X, COMBO_END};
// const uint16_t PROGMEM jc[] = {LSFT_J, KC_C, COMBO_END};
// const uint16_t PROGMEM jv[] = {LSFT_J, KC_V, COMBO_END};
// const uint16_t PROGMEM jb[] = {LSFT_J, KC_B, COMBO_END};
const uint16_t PROGMEM j_1[] = {NUM_SPC, KC_1, COMBO_END};
const uint16_t PROGMEM j_2[] = {NUM_SPC, KC_2, COMBO_END};
const uint16_t PROGMEM j_3[] = {NUM_SPC, KC_3, COMBO_END};
const uint16_t PROGMEM j_4[] = {NUM_SPC, KC_4, COMBO_END};
const uint16_t PROGMEM j_5[] = {NUM_SPC, KC_5, COMBO_END};

const uint16_t PROGMEM jq[] = {NUM_SPC, KC_Q, COMBO_END};
const uint16_t PROGMEM jw[] = {NUM_SPC, KC_W, COMBO_END};
const uint16_t PROGMEM je[] = {NUM_SPC, KC_E, COMBO_END};
const uint16_t PROGMEM jr[] = {NUM_SPC, KC_R, COMBO_END};
const uint16_t PROGMEM jt[] = {NUM_SPC, KC_T, COMBO_END};

const uint16_t PROGMEM ja[] = {NUM_SPC, KC_A, COMBO_END};
const uint16_t PROGMEM js[] = {NUM_SPC, KC_S, COMBO_END};
const uint16_t PROGMEM jd[] = {NUM_SPC, KC_D, COMBO_END};
const uint16_t PROGMEM jf[] = {NUM_SPC, KC_F, COMBO_END};
const uint16_t PROGMEM jg[] = {NUM_SPC, KC_G, COMBO_END};

const uint16_t PROGMEM jz[] = {NUM_SPC, KC_Z, COMBO_END};
const uint16_t PROGMEM jx[] = {NUM_SPC, KC_X, COMBO_END};
const uint16_t PROGMEM jc[] = {NUM_SPC, KC_C, COMBO_END};
const uint16_t PROGMEM jv[] = {NUM_SPC, KC_V, COMBO_END};
const uint16_t PROGMEM jb[] = {NUM_SPC, KC_B, COMBO_END};

const uint16_t PROGMEM w1[] = {NUM_SPC, NAV_BS, COMBO_END};

combo_t key_combos[] = {
     [F_6] = COMBO(f_6, LSFT(KC_6)),
     [F_7] = COMBO(f_7, LSFT(KC_7)),
     [F_8] = COMBO(f_8, LSFT(KC_8)),
     [F_9] = COMBO(f_9, LSFT(KC_9)),
     [F_0] = COMBO(f_0, LSFT(KC_0)),

     [FY] = COMBO(fy, LSFT(KC_Y)),
     [FU] = COMBO(fu, LSFT(KC_U)),
     [FI] = COMBO(fi, LSFT(KC_I)),
     [FO] = COMBO(fo, LSFT(KC_O)),
     [FP] = COMBO(fp, LSFT(KC_P)),

     [FH]   = COMBO(fh, LSFT(KC_H)),
     [FJ]   = COMBO(fj, LSFT(KC_J)),
     [FK]   = COMBO(fk, LSFT(KC_K)),
     [FL]   = COMBO(fl, LSFT(KC_L)),
     [FSCN] = COMBO(fscn, LSFT(KC_SCLN)),

     [FN]    = COMBO(fn, LSFT(KC_N)),
     [FM]    = COMBO(fm, LSFT(KC_M)),
     [FCOMM] = COMBO(fcomm, LSFT(KC_COMM)),
     [FDOT]  = COMBO(fdot, LSFT(KC_DOT)),
     [FSLSH] = COMBO(fslsh, LSFT(KC_SLSH)),


     [J_1] = COMBO(j_1, LSFT(KC_1)),
     [J_2] = COMBO(j_2, LSFT(KC_2)),
     [J_3] = COMBO(j_3, LSFT(KC_3)),
     [J_4] = COMBO(j_4, LSFT(KC_4)),
     [J_5] = COMBO(j_5, LSFT(KC_5)),

     [JQ] = COMBO(jq, LSFT(KC_Q)),
     [JW] = COMBO(jw, LSFT(KC_W)),
     [JE] = COMBO(je, LSFT(KC_E)),
     [JR] = COMBO(jr, LSFT(KC_R)),
     [JT] = COMBO(jt, LSFT(KC_T)),

     [JA] = COMBO(ja, LSFT(KC_A)),
     [JS] = COMBO(js, LSFT(KC_S)),
     [JD] = COMBO(jd, LSFT(KC_D)),
     [JF] = COMBO(jf, LSFT(KC_F)),
     [JG] = COMBO(jg, LSFT(KC_G)),

     [JZ] = COMBO(jz, LSFT(KC_Z)),
     [JX] = COMBO(jx, LSFT(KC_X)),
     [JC] = COMBO(jc, LSFT(KC_C)),
     [JV] = COMBO(jv, LSFT(KC_V)),
     [JB] = COMBO(jb, LSFT(KC_B)),

     [W1] = COMBO(w1, LSFT(KC_B)),
};

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
    case PNTR_OFF:
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

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case LAYER_MIRYOKU: 
    case LAYER_COMBO:
        combo_enable();
        break;
    default: //  for any other layers, or the default layer
        combo_disable();
        break;
    }
    return state;
}
