
#include "color.hpp"

using namespace Engine;

const Color Color::RED    = Color{255, 0, 0};
const Color Color::GREEN  = Color{0, 255, 0};
const Color Color::BLUE   = Color{0, 0, 255};
const Color Color::YELLOW = Color{255, 255, 0};
const Color Color::BLACK  = Color{0, 0, 0};
const Color Color::WHITE  = Color{255, 255, 255};

Engine::Color::Color(Uint8 r1, Uint8 g1, Uint8 b1, Uint8 a1)
    : r(r1), g(g1), b(b1), a(a1)
{ }

Engine::Color::Color(const Color & color)
    : r(color.r), g(color.g), b(color.b), a(color.a)
{ }

Color Color::operator=(const Color & color) const
{
    return Color{color.r, color.g, color.b, color.a};
}

bool Engine::operator==(const Color & c1, const Color & c2)
{
    return c1.r == c2.r
        && c1.g == c2.g
        && c1.b == c2.b
        && c1.a == c2.a;
}

bool Engine::operator!=(const Color & c1, const Color & c2)
{
    return !(c1 == c2);
}
