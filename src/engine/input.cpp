
#include "input.hpp"

#include <cstring>
#include <SDL.h>

using namespace Engine;

Input::Input()
    : m_keyboardStatePtr(SDL_GetKeyboardState(NULL))
{
    int x, y;
    m_oldMouseState = m_mouseState = SDL_GetMouseState(&x, &y);

    m_mousePos.x = x;
    m_mousePos.y = y;

    memcpy(&m_keyboardState, m_keyboardStatePtr, Keycode::KEY_MAX);
    memcpy(&m_oldKeyboardState, m_keyboardStatePtr, Keycode::KEY_MAX);
}

Vect2f Input::mousePosition() const
{
    return m_mousePos;
}

bool Input::isButtonPressed(MouseButton btn) const
{
    return m_mouseState & SDL_BUTTON(btn);
}

bool Input::isButtonReleased(MouseButton btn) const
{
    return m_oldMouseState & SDL_BUTTON(btn) && !isButtonPressed(btn);
}

bool Input::isKeyPressed(Keycode key) const
{
    return m_keyboardState[key];
}

bool Input::isKeyReleased(Keycode key) const
{
    return m_oldKeyboardState[key] && !isKeyPressed(key);
}

void Input::update()
{
    int x, y;
    m_oldMouseState = m_mouseState;
    m_mouseState = SDL_GetMouseState(&x, &y);

    m_mousePos.x = x;
    m_mousePos.y = y;

    memcpy(&m_oldKeyboardState, &m_keyboardState, Keycode::KEY_MAX);
    memcpy(&m_keyboardState, m_keyboardStatePtr, Keycode::KEY_MAX);
}
