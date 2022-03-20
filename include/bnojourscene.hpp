/**
 * @file bnojourscene.hpp
 * @brief Simple test scene for the game engine and text components
 */

#ifndef __BNOJOURSCENE_H__
#define __BNOJOURSCENE_H__

#include "scene.hpp"

#include "textcomponent.hpp"
#include <memory>

class BnojourScene
    : public Engine::Scene
{
public:
    BnojourScene();

    virtual void update(const Engine::Input &in) override;

private:
    std::shared_ptr<Engine::TextComponent> m_text;

};

#endif
