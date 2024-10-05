/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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


// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

#define HOME_Z LGUI_T(KC_Z)
#define HOME_C LCTL_T(KC_C)
#define HOME_X LSFT_T(KC_X)
#define HOME_V LALT_T(KC_V)
// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RCTL_T(KC_SCLN)

#define NAV_LTAB LALT_T(KC_TAB)
#define NAV_RTAB LGUI_T(KC_TAB)

#define NAV_LCTL OSM(MOD_LCTL)
#define NAV_LALT OSM(MOD_LALT)
#define NAV_LGUI OSM(MOD_LGUI)
#define NAV_LSFT OSM(MOD_LSFT)

enum layers {
    _MAIN,
    _NUM_NAV,
    _OSM_MOUSE_NAV,
    _SYM,
    _MEDIA,
};

#define LAYER_SPC LT(_OSM_MOUSE_NAV, KC_SPC)


#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_BLUE);
            }
        }
    }
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];


                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    switch (get_highest_layer(layer_state)) {
                        case _NUM_NAV:
                            rgb_matrix_set_color(index, RGB_SPRINGGREEN);
                            break;
                        case _OSM_MOUSE_NAV:
                            rgb_matrix_set_color(index, RGB_MAGENTA);
                            break;
                        case _SYM:
                            rgb_matrix_set_color(index, RGB_GOLD);
                            break;
                        case _MEDIA:
                            rgb_matrix_set_color(index, RGB_RED);
                            break;
                        default:
                            rgb_matrix_set_color(index, RGB_CORAL);
                            break;
                    }

                }
            }
        }
    }
    return false;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_P(PSTR("main\n"), false);
            break;
        case _NUM_NAV:
            oled_write_P(PSTR("nav\n"), false);
            break;
        case _OSM_MOUSE_NAV:
            oled_write_P(PSTR("mouse\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("sym\n"), false);
            break;
        case _MEDIA:
            oled_write_P(PSTR("media\n"), false);
            break;

        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("xxx"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,    HOME_A, HOME_S,   HOME_D,  HOME_F,  KC_G,                         KC_H,  HOME_J,  HOME_K,  HOME_L, HOME_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,    KC_Z,    KC_X,   KC_C,    KC_V,     KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                  XXXXXXX,   MO(_NUM_NAV), LAYER_SPC,     KC_ENT,   MO(_SYM), XXXXXXX
                                      //`--------------------------'  `--------------------------'

  ),

    [_NUM_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, NAV_LTAB, NAV_RTAB, KC_LSFT, KC_ENT,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_BSPC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CAPS, KC_PGUP, KC_PGDN, KC_ESC, XXXXXXX,                     KC_HOME,  KC_ESC, XXXXXXX, KC_END,   KC_DEL,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     _______,   MO(_MEDIA), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [_OSM_MOUSE_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                    QK_LOCK, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, NAV_LCTL, NAV_LALT, NAV_LGUI, NAV_LSFT, XXXXXXX,                   MS_LEFT, MS_DOWN,  MS_UP,MS_RGHT, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        XXXXXXX, XXXXXXX, _______,     _______, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, KC_EXLM, KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        XXXXXXX, MO(_MEDIA), KC_SPC,     _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [_MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_SAI, RGB_VAI, RGB_HUI, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_SAD, RGB_VAD, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};


/*
    [_OSM_MOUSE_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        XXXXXXX, MO(_MEDIA), KC_SPC,     _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
*/
/*
block {
   color: #99F5FF; / * RGB_AZURE       * /
   color: #000000; / * RGB_BLACK       * /
   color: #0000FF; / * RGB_BLUE        * /
   color: #80FF00; / * RGB_CHARTREUSE  * /
   color: #FF7C4D; / * RGB_CORAL       * /
   color: #00FFFF; / * RGB_CYAN        * /
   color: #FFD900; / * RGB_GOLD        * /
   color: #D9A521; / * RGB_GOLDENROD   * /
   color: #00FF00; / * RGB_GREEN       * /
   color: #FF00FF; / * RGB_MAGENTA     * /
   color: #FF8000; / * RGB_ORANGE      * /
   color: #FF80BF; / * RGB_PINK        * /
   color: #7A00FF; / * RGB_PURPLE      * /
   color: #FF0000; / * RGB_RED         * /
   color: #00FF80; / * RGB_SPRINGGREEN * /
   color: #008080; / * RGB_TEAL        * /
   color: #476E6A; / * RGB_TURQUOISE   * /
   color: #FFFFFF; / * RGB_WHITE       * /
   color: #FFFF00; / * RGB_YELLOW      * /
}
*/
