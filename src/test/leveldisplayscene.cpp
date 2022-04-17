
#include "leveldisplayscene.hpp"

#include "game.hpp"
#include "keycode.hpp"
#include "levelrenderer.hpp"
#include "vect2.hpp"

LevelDisplayScene::LevelDisplayScene()
{
    const Engine::Vect2f center = Engine::Game::instance()->center();
    const size_t height = Engine::Game::instance()->height();

    m_levels.emplace_back(LevelRenderer{center, height, LevelType::PLUS});
    m_levels.emplace_back(LevelRenderer{center, height,  LevelType::SQUARE});
    m_levels.emplace_back(LevelRenderer{center, height,  LevelType::TRIANGLE});
}

void LevelDisplayScene::update(const Engine::Input &in)
{
    if(in.isKeyReleased(Engine::KEY_Q) || in.isKeyReleased(Engine::KEY_LEFT))
    {
        if(m_currentLevel == 0)
            m_currentLevel = m_levels.size();
        m_currentLevel -= 1;
    }
    else if(in.isKeyReleased(Engine::KEY_D) || in.isKeyReleased(Engine::KEY_RIGHT))
    {
        m_currentLevel += 1;
    }
}

void LevelDisplayScene::render(const Engine::Output &out) const
{
    m_levels[m_currentLevel % m_levels.size()].render(out);
}
