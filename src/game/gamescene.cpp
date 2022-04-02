
#include "gamescene.hpp"

#include "enemy.hpp"
#include "game.hpp"
#include "player.hpp"
#include "scene.hpp"
#include <cassert>

GameScene::GameScene(LevelType level)
    : m_level(new LevelRenderer{Engine::Game::instance()->center(), level}),
        m_player(new Player{m_level})
{
    // Insert level first to be in background, if not we should render it manually
    m_objects.emplace_back(m_level);

    m_objects.emplace_back(m_player);

    createEnemy(SQUARE_MIDDLE);
}

void GameScene::createEnemy(EnemyShape type)
{
    //TO UPGRADE where enemy (random)
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(0, 0.5, type);
    m_enemies.insert(enemy);
    m_objects.emplace_back(enemy);
}

size_t GameScene::nbLine() const
{
    return m_level->laneCount();
}

void GameScene::update(const Engine::Input &in)
{
    Engine::Scene::update(in);
    
    for (const auto& e : m_enemies)
    {
        assert(e.get());
        if (e->position() >= 100)
        {
            // TODO Do appropiate thing according to game rules
            //m_enemies.erase(e);
            remove(e);
        }
    }

    // TODO Real spawn system
    static int count = 0, lane = 0;
    count += 1;
    if(count >= 10)
    {
        count = 0;

        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
            lane++ % m_level->laneCount(), 0.5, EnemyShape::SQUARE_MIDDLE);
        m_enemies.insert(enemy);
        m_objects.emplace_back(enemy);
    }
}

void GameScene::render(const Engine::Output &out) const
{
    Engine::Scene::render(out);

    m_level->clearEnemy();
    for (const auto& e : m_enemies)
        m_level->drawEnemy(e);
}
