/**
 * @file keycode.hpp
 * @brief Wrapper for SDL Scancodes as Keyboard keys
 */

#ifndef __KEYCODE_H__
#define __KEYCODE_H__

#include <SDL.h>

namespace Engine
{

enum Keycode : int
{
    KEY_0 = SDLK_0,
    KEY_1 = SDLK_1,
    KEY_2 = SDLK_2,
    KEY_3 = SDLK_3,
    KEY_4 = SDLK_4,
    KEY_5 = SDLK_5,
    KEY_6 = SDLK_6,
    KEY_7 = SDLK_7,
    KEY_8 = SDLK_8,
    KEY_9 = SDLK_9,

    KEY_A = SDLK_a,
    KEY_B = SDLK_b,
    KEY_C = SDLK_c,
    KEY_D = SDLK_d,
    KEY_E = SDLK_e,
    KEY_F = SDLK_f,
    KEY_G = SDLK_g,
    KEY_H = SDLK_h,
    KEY_I = SDLK_i,
    KEY_J = SDLK_j,
    KEY_K = SDLK_k,
    KEY_L = SDLK_l,
    KEY_M = SDLK_m,
    KEY_N = SDLK_n,
    KEY_O = SDLK_o,
    KEY_P = SDLK_p,
    KEY_Q = SDLK_q,
    KEY_R = SDLK_r,
    KEY_S = SDLK_s,
    KEY_T = SDLK_t,
    KEY_U = SDLK_u,
    KEY_V = SDLK_v,
    KEY_W = SDLK_w,
    KEY_X = SDLK_x,
    KEY_Y = SDLK_y,
    KEY_Z = SDLK_z,

    KEY_SPACE      = SDLK_SPACE,
    KEY_ENTER      = SDLK_RETURN,
    KEY_ESC        = SDLK_ESCAPE,
    KEY_LEFT_CTRL  = SDLK_LCTRL,
    KEY_RIGHT_CTRL = SDLK_RCTRL,
    KEY_LEFT_ALT   = SDLK_LALT,
    KEY_RIGHT_ALT  = SDLK_RALT,

    KEY_UP    = SDLK_UP,
    KEY_DOWN  = SDLK_DOWN,
    KEY_LEFT  = SDLK_LEFT,
    KEY_RIGHT = SDLK_RIGHT
};

};

#endif
