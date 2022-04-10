
#include "input.hpp"
#include "SDL_events.h"

#include <cstring>
#include <SDL.h>

using namespace Engine;

Input::Input()
{
    int x, y;
    m_oldMouseState = m_mouseState = SDL_GetMouseState(&x, &y);

    m_mousePos.x = x;
    m_mousePos.y = y;
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
    return m_keyboardPressed.contains(key);
}

bool Input::isKeyReleased(Keycode key) const
{
    return m_oldKeyboardPressed.contains(key) && !isKeyPressed(key);
}

void Input::update()
{
    int x, y;
    m_oldMouseState = m_mouseState;
    m_mouseState = SDL_GetMouseState(&x, &y);

    m_mousePos.x = x;
    m_mousePos.y = y;

    m_oldKeyboardPressed = m_keyboardPressed;
}

void Input::keyboardEvent(struct SDL_KeyboardEvent ke)
{
    if(ke.state == SDL_PRESSED)
    {
        m_keyboardPressed.insert((Keycode) ke.keysym.sym);
    }
    else if(ke.state == SDL_RELEASED)
    {
        m_keyboardPressed.erase((Keycode) ke.keysym.sym);
    }
}
