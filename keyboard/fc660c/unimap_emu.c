#include "action.h"
#include "actionmap.h"
#include "hook.h"
#include "fc660c.h"

/* id for user defined functions */
enum function_id {
    ESCX,
};

#define AC_L1       ACTION_LAYER_MOMENTARY(1)
#define AC_L2       ACTION_LAYER_MOMENTARY(2)
#define AC_1CTL     ACTION_LAYER_MODS(1, MOD_LCTL)
#define AC_ESCX     ACTION_FUNCTION_TAP(ESCX)

// emulates FC660C default keymap
#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    [0] = KMAP(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     VOLU,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     VOLD,
        1CTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,UP,
        LCTL,LALT,LGUI,          SPC,                     RGUI,RALT,L1,  LEFT,DOWN,RGHT
    ),
    [1] = KMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,    TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,ESCX,TRNS,TRNS,    MUTE,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          CAPS,PGUP,
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,L1,  HOME,PGDN,END
    ),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case ESCX:
            if (record->event.pressed) {
                unregister_mods(MOD_BIT(KC_LCTL));
                register_code(KC_ESC);
                unregister_code(KC_ESC);
                register_mods(MOD_BIT(KC_LCTL));
            }
            break;
    }
}
