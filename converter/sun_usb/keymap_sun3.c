/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "util.h"
#include "keymap.h"


/* Sun type 3 keyboard 
,-------.  ,-----------------------------------------------------------.  ,-----------.
| 01| 03|  | 05| 06|     08|     0A|     0C|     0E|     10| 11| 12| 2B|  | 15| 16| 17|
|-------|  |-----------------------------------------------------------|  |-----------|
| 19| 1A|  | 1D| 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29| 58| 2A|  | 2D| 2E| 2F|
|-------|  |-----------------------------------------------------------|  |-----------|
| 31| 33|  |  35 | 36| 37| 38| 39| 3A| 3B| 3C| 3D| 3E| 3F| 40| 41| 42  |  | 44| 45| 46|
|-------|  |-----------------------------------------------------------|  |-----------|
| 48| 49|  |  4C  | 4D| 4E| 4F| 50| 51| 52| 53| 54| 55| 56| 57|   59   |  | 5B| 5C| 5D|
|-------|  |-----------------------------------------------------------|  |-----------|
| 5F| 61|  |   63   | 64| 65| 66| 67| 68| 69| 6A| 6B| 6C| 6D|    6E| 6F|  | 70| 71| 72|
`-------'  |-----------------------------------------------------------|  `-----------'
           | 77 | 78  |               79                  | 7A  |   13 |  
           `-----------------------------------------------------------'  
*/


#define KEYMAP( \
    K01,K03,  K05,K06,    K08,    K0A,    K0C,    K0E,    K10,K11,K12,K2B,  K15,K16,K17, \
    K19,K1A,  K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K58,K2A,  K2D,K2E,K2F, \
    K31,K33,  K35, K36,K37,K38,K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,   K42,  K44,K45,K46, \
    K48,K49,  K4C,  K4D,K4E,K4F,K50,K51,K52,K53,K54,K55,K56,K57,      K59,  K5B,K5C,K5D, \
    K5F,K61,  K63,   K64,K65,K66,K67,K68,K69,K6A,K6B,K6C,K6D,     K6E,K6F,  K70,K71,K72, \
              K77,K78,                    K79,                    K7A,K13                \
) { \
    { KC_NO,    KC_##K01, KC_NO,    KC_##K03, KC_NO,    KC_##K05, KC_##K06, KC_NO    }, \
    { KC_##K08, KC_NO,    KC_##K0A, KC_NO,    KC_##K0C, KC_NO,    KC_##K0E, KC_NO    }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_NO,    KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_NO,    KC_##K19, KC_##K1A, KC_NO,    KC_NO,    KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_NO,    KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_NO,    KC_##K31, KC_NO,    KC_##K33, KC_NO,    KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_NO,    KC_##K44, KC_##K45, KC_##K46, KC_NO    }, \
    { KC_##K48, KC_##K49, KC_NO,    KC_NO,    KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_NO,    KC_##K5B, KC_##K5C, KC_##K5D, KC_NO,    KC_##K5F }, \
    { KC_NO,    KC_##K61, KC_NO,    KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K77 }, \
    { KC_##K78, KC_##K79, KC_##K7A, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}

// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
const uint8_t PROGMEM fn_layer[] = {
    2,              // Fn0
    3,              // Fn1
    4,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_SCLN,        // Fn1
    KC_SLSH,        // Fn2
    KC_NO,          // Fn3
    KC_NO,          // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    KEYMAP(
    F10, F11,   F1, F2,     F3,     F4,     F5,     F6,      F7,  F8, F9,  BSPC,   VOLD, MUTE,   VOLU,
    F12, F13,   ESC, 1,  2,  3,  4,  5,  6,  7,  8,  9,  0,MINS, EQL, BSLS, GRV,   MPRV, MPLY,   MNXT,
    F14, F15,   TAB, Q,  W,  E,  R,  T,  Y,  U,  I,  O,  P,   LBRC,RBRC,    DEL,   HOME, UP,     PGUP,
    F16, F17,   LCTL, A,  S,  D,  F,  G,  H,  J,  K,  L,  SCLN,QUOT,        ENT,   LEFT, INSERT, RIGHT, 
    F18, F19,   LSFT,  Z,  X,  C,  V,  B,  N,  M,  COMM,DOT,SLSH,     RSFT,RCTL,   END,  DOWN,   PGDOWN,
                LGUI, LALT,                 SPC,                      RALT,RGUI
    ),
    /*
    // 0: default
    SHORT_TYPE(
        STOP, F1,F2,F3,F4, F5, F6,   CUT,PASTE,COPY,PWR,    INS, HOME,PGUP,
              F7,F8,F9,F10,F11,F12,                         DEL, END, PGDN,
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV,
        TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,    BSPC,
        LCTL,  A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,        ENT,
        LSFT,   Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,  RALT,UP,  RSFT,
        CAPS,LALT,LGUI,            SPC,              RGUI,APP, NLCK,LEFT,DOWN,RGHT
    ),
    // 1: with layer keys
    SHORT_TYPE(
        ESC,  F1,F2,F3,F4, F5, F6,   CUT,PASTE,COPY,PWR,    INS, HOME,PGUP,
              F7,F8,F9,F10,F11,F12,                         DEL, END, PGDN,
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV,
        TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,    BSPC,
        LCTL,  A,   S,   D,   F,   G,   H,   J,   K,   L,   FN1, QUOT,        ENT,
        LSFT,   Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2,   RSFT,UP,  FN0,
        CAPS,LALT,LGUI,            SPC,              RGUI,RALT,FN0, LEFT,DOWN,RGHT
    ),
    // 2: HHKB
    SHORT_TYPE(
        ESC,  F1,F2,F3,F4, F5, F6,   CUT,PASTE,COPY,PWR,    INS, HOME,PGUP,
              F7,F8,F9,F10,F11,F12,                         DEL, END, PGDN,
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
        CAPS, NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  NO,      BSPC,
        LCTL,  VOLD,VOLU,MUTE,NO,  NO,  NO,  NO,  HOME,PGUP,LEFT,RGHT,        ENT,
        LSFT,   Z,   X,   C,   V,   B,   NO,  NO,  END, PGDN,DOWN,  RSFT,PGUP,FN0,
        CAPS,LALT,LGUI,            SPC,              RGUI,RALT,FN0, HOME,PGDN,END
    ),
    // 3: Mousekey
    SHORT_TYPE(
        ESC,  F1,F2,F3,F4, F5, F6,   CUT,PASTE,COPY,PWR,    INS, HOME,PGUP,
              F7,F8,F9,F10,F11,F12,                         DEL, END, PGDN,
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
        CAPS, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,      BSPC,
        LCTL,  NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,FN1, NO,          ENT,
        LSFT,   NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,NO,  NO,  NO,    RSFT,UP,  NO,
        CAPS,LALT,LGUI,            BTN1,             RGUI,RALT,NO,  LEFT,DOWN,RGHT
    ),
    // 4: Cursor
    SHORT_TYPE(
        ESC,  F1,F2,F3,F4, F5, F6,   CUT,PASTE,COPY,PWR,    INS, HOME,PGUP,
              F7,F8,F9,F10,F11,F12,                         DEL, END, PGDN,
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
        CAPS, NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,  NO,  NO,      BSPC,
        LCTL,  NO,  NO,  NO,  NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,          ENT,
        LSFT,   NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN2,   RSFT,UP,  NO,
        CAPS,LALT,LGUI,            BTN1,             RGUI,RALT,NO,  LEFT,DOWN,RGHT
    ),
    */
};
