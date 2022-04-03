
#include "gamescene.hpp"

#include "enemy.hpp"
#include "game.hpp"
#include "player.hpp"
#include "scene.hpp"
#include <cassert>
#include <memory>

GameScene::GameScene(LevelType level)
    : m_level{new LevelRenderer{Engine::Game::instance()->center(), level}},
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
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(0, 0.5, type, m_level);
    m_enemies.emplace_back(enemy);
    m_objects.emplace_back(enemy);
}

size_t GameScene::nbLine() const
{
    return m_level->laneCount();
}

void GameScene::update(const Engine::Input &in)
{
    Engine::Scene::update(in);
    
    std::vector<std::shared_ptr<Enemy>> removed;
    for (const auto& e : m_enemies)
    {
        if (e->position() >= 100)
        {
            // TODO Do appropiate thing according to game rules
            
            removed.emplace_back(e);
            remove(e);
        }
    }
    for(const auto& e : removed)
    {
        m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), e),
            m_enemies.end());
    }

    // TODO Real spawn system
    static int count = 0, lane = 0;
    count += 1;
    if(count >= 10)
    {
        count = 0;

        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
            lane++ % m_level->laneCount(), 0.5, EnemyShape::SQUARE_MIDDLE, m_level);
        m_enemies.emplace_back(enemy);
        m_objects.emplace_back(enemy);
    }
}
