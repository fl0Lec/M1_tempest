/**
 * @file levelbutton.hpp
 * @brief Button that draws a level
 */

#ifndef __LEVELBUTTON_H__
#define __LEVELBUTTON_H__

#include "button.hpp"

#include "levelrenderer.hpp"
#include "vect2.hpp"

class LevelButton
    : public Engine::Button
{
public:
    LevelButton(const Engine::Vect2f& pos, const Engine::Vect2f& size,
        LevelType type, Engine::Callback onClick = nullptr,
        Engine::Callback onHover = nullptr);

    virtual void render(const Engine::Output &out) const override;

private:
    LevelRenderer m_levelRenderer;

};

#endif
