
#include "missile.hpp"

#include "vect2.hpp"

using namespace Engine;

const Color Missile::MISSILE_COLOR = Color::MAGENTA;

Missile::Missile(uint line, const LevelRenderer& level)
    : Entity(line, MAX_POSITION-1), m_level(level)
{ }

void Missile::update([[maybe_unused]] const Engine::Input &in)
{
    m_position -= SPEED;
}

void Missile::render(const Engine::Output &out) const
{
    std::pair<Line2f, Line2f> lines = m_level.laneLines(m_line);
    const Vect2f line1{lines.first.first, lines.first.second},
        line2{lines.second.first, lines.second.second};

    // TODO Maybe use homothetie
    const float top    = (m_position + WIDTH/2) / MAX_POSITION;
    const float bottom = (m_position - WIDTH/2) / MAX_POSITION;

    const Vect2f base = Vect2f::center(lines.first.first, lines.second.first);
    
    float h;
    h = (m_position/100) * (m_position/100);
    out.setColor(MISSILE_COLOR);
    out.drawLine({
        Vect2f::homothetie(h, (base  + Vect2f::center(line1 * top, line2 * top)), base),
        Vect2f::homothetie(h, (base + Vect2f::center(line1 * bottom, line2 * bottom)), base),
    });
}
