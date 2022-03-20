
#include "textcomponent.hpp"
#include "hershey.hpp"
#include "vect2.hpp"

#include <numeric>

using namespace Engine;
using namespace std;

TextComponent::TextComponent(const Vect2f & center, const std::string & text,
    const Color & color)
    : m_center(center), m_text(text), m_color(color)
{
    computePosition();
}

void TextComponent::move(const Vect2f & center)
{
    m_center = center;
    computePosition();
}

void TextComponent::setText(const std::string & text)
{
    m_text = text;
    computePosition();
}

void TextComponent::setColor(const Color & color)
{
    m_color = color;
}

const Vect2f & TextComponent::position() const
{
    return m_position;
}

const Vect2f & TextComponent::center() const
{
    return m_center;
}

const std::string & TextComponent::text() const
{
    return m_text;
}

const Color & TextComponent::color() const
{
    return m_color;
}

void TextComponent::update(const Input &in)
{
    (void) in;
}

void TextComponent::render(const Output &out) const
{
    out.setColor(m_color);

    Vect2f start{m_position};
    for(const auto& c : m_text)
    {
        Hershey::drawLetter(out, c, start);
        start.x += Hershey::getLetterWidth(c) + INTER_LETTER_SPACE;
    }
}

void TextComponent::computePosition()
{
    const int width =
        std::reduce(m_text.cbegin(), m_text.cend(), 0, [](const auto& acc, const auto& c)
        {
            return acc + Hershey::getLetterWidth(c);
        })
        + INTER_LETTER_SPACE * (m_text.size() - 1);

    m_position = Vect2f(m_center.x - width / 2.0, m_center.y);
}
