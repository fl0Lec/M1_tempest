
#include "levelbutton.hpp"
#include "button.hpp"
#include "vect2.hpp"

LevelButton::LevelButton(const Engine::Vect2f& pos, const Engine::Vect2f& size,
        LevelType type, Engine::Callback onClick, Engine::Callback onHover)
    : Engine::Button(pos, size, "", onClick, onHover),
        m_levelRenderer{Engine::Vect2f::center(pos, pos+size), (size_t) size.x, type}
{}

void LevelButton::render(const Engine::Output &out) const
{
    Engine::Button::render(out);
    m_levelRenderer.render(out);
}
