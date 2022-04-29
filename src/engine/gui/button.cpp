
#include "button.hpp"

#include <memory>

#include "input.hpp"
#include "textcomponent.hpp"
#include "vect2.hpp"

using namespace Engine;

const Color Button::SELECTED_COLOR = Color::YELLOW;
const Color Button::PRESSED_COLOR  = Color::RED;

Button::Button(const Vect2f& pos, const Vect2f& size, const std::string& text,
        Callback onClick, Callback onHover)
    : m_pos{pos}, m_size{size}, m_onClick{onClick}, m_onHover{onHover},
        m_text{new TextComponent{Vect2f::center(pos, pos+size), text}}
{ }

const Vect2f& Button::pos() const
{
    return m_pos;
}

const Vect2f& Button::size() const
{
    return m_size;
}

const std::string& Button::text() const
{
    return m_text->text();
}

bool Button::isSelected() const
{
    return m_isSelected;
}

bool Button::isPressed() const
{
    return m_isPressed;
}

void Button::setPos(const Vect2f& pos)
{
    m_pos = pos;
    m_text->move(Vect2f::center(pos, pos+m_size));
}

void Button::setSize(const Vect2f& size)
{
    m_size = size;
    m_text->move(Vect2f::center(m_pos, m_pos+size));
}

void Button::setText(const std::string& text)
{
    m_text->setText(text);
}

void Button::setSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

void Button::setOnClickAction(Callback onClick)
{
    m_onClick = onClick;
}

void Button::setOnHoverAction(Callback onHover)
{
    m_onHover = onHover;
}

void Button::click()
{
    if(m_onClick)
        m_onClick(thisShared());
}

std::shared_ptr<Button> Button::thisShared()
{
    auto null_deleter = [&](Button *){};

    return std::shared_ptr<Button>{this, null_deleter};
}

void Button::update(const Input &in)
{
    const auto mouse = in.mousePosition();
    const auto bounds = m_pos + m_size;

    const bool mouseInside = mouse.x >= m_pos.x && mouse.y >= m_pos.y 
        && mouse.x <= bounds.x && mouse.y <= bounds.y;

    // Send hover signal when hover starts
    if(mouseInside && !m_isHovered)
    {
        m_isHovered = true;
        if(m_onHover)
            m_onHover(thisShared());
    }
    else if(!mouseInside && m_isHovered)
        m_isHovered = false;

    // Manage pressed status and send click signal if released inside button
    if(in.isButtonPressed(MouseButton::MOUSE_LEFT) && mouseInside
        && !m_isPressed)
    {
        m_isPressed = true;
    }
    else if(in.isButtonReleased(MouseButton::MOUSE_LEFT) && m_isPressed)
    {
        if(mouseInside && m_onClick)
            m_onClick(thisShared());
        m_isPressed = false;
    }
}

void Button::render(const Output &out) const
{
    if(m_isPressed || m_isSelected)
    {
        if(m_isPressed)
            out.setColor(PRESSED_COLOR);
        else // isSelected
            out.setColor(SELECTED_COLOR);

        out.drawLine(m_pos, m_pos + Vect2f{m_size.x, 0});
        out.drawLine(m_pos, m_pos + Vect2f{0, m_size.y});
        out.drawLine(m_pos + Vect2f{m_size.x, 0}, m_pos + m_size);
        out.drawLine(m_pos + Vect2f{0, m_size.y}, m_pos + m_size);
    }

    m_text->render(out);
}
