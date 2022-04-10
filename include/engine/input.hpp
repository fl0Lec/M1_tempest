/**
 * @file input.hpp
 * @brief Wrapper for everything related to the user's input
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL.h>

#include <set>

#include "keycode.hpp"
#include "vect2.hpp"

namespace Engine
{

// Wrapper for mouse buttons codes
enum MouseButton
{
    MOUSE_LEFT = SDL_BUTTON_LEFT,
    MOUSE_MIDDLE = SDL_BUTTON_MIDDLE,
    MOUSE_RIGHT = SDL_BUTTON_RIGHT,
};

/**
 * @brief Wrapper for everything related to keyboard and mouse input
 */
class Input
{
public:
    Input();

    /**
     * @brief Get current pointer coordinates (relative to window)
     */
    Vect2f mousePosition() const;

    /**
     * @brief Check if mouse button is pressed
     */
    bool isButtonPressed(MouseButton btn) const;

    /**
     * @brief Check if mouse button was just released
     */
    bool isButtonReleased(MouseButton btn) const;

    /**
     * @brief Check if a keyboard key is pressed
     */
    bool isKeyPressed(Keycode key) const;

    /**
     * @brief Check if a keyboard key was just released
     */
    bool isKeyReleased(Keycode key) const;

    void update();

    void keyboardEvent(struct SDL_KeyboardEvent ke);

private:
    Vect2f m_mousePos;
    Uint32 m_mouseState;
    Uint32 m_oldMouseState;

    std::set<Keycode> m_keyboardPressed;
    std::set<Keycode> m_oldKeyboardPressed;
};

};

#endif
