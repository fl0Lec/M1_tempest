
#include "output.hpp"

using namespace Engine;

Output::Output()
{ }

Output::Output(SDL_Renderer * sdl_render)
    : m_render(sdl_render)
{ }

void Output::clear(Color color) const
{
    setColor(color);
    SDL_RenderClear(m_render);
}

void Output::setColor(Color color) const
{
    SDL_SetRenderDrawColor(m_render, color.r, color.g, color.b, color.a);
}

void Output::drawPoint(Vect2f p) const
{
    SDL_RenderDrawPointF(m_render, p.x, p.y);
}

void Output::drawLine(Vect2f s, Vect2f d) const
{
    SDL_RenderDrawLineF(m_render, s.x, s.y, d.x, d.y);
}

void Output::render() const
{
    SDL_RenderPresent(m_render);
}
