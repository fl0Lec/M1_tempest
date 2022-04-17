
#include "bnojourscene.hpp"

#include "game.hpp"
#include "levelrenderer.hpp"
#include "textcomponent.hpp"
#include "vect2.hpp"

using namespace Engine;

BnojourScene::BnojourScene()
    : m_text(new TextComponent{Vect2f{10, 10}, "Bnojour"}),
        m_levelRenderer(new LevelRenderer(Game::instance()->center(),
            Game::instance()->height(),
            LevelType::SQUARE))
{
    m_objects.emplace_back(m_levelRenderer);
    m_objects.emplace_back(m_text);
}

void BnojourScene::update(const Engine::Input &in)
{
    m_text->move(in.mousePosition());
}
