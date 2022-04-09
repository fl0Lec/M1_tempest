
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
    addEntity(enemy);
}

void GameScene::addEntity(const std::shared_ptr<Entity>& entity)
{
    m_entities.emplace_back(entity);
    m_objects.emplace_back(entity);
}

void GameScene::removeEntity(const std::shared_ptr<Entity>& entity)
{
    remove(entity);
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity),
            m_entities.end());
}

size_t GameScene::nbLine() const
{
    return m_level->laneCount();
}

void GameScene::update(const Engine::Input &in)
{
    Engine::Scene::update(in);
    
    checkEnemies();
    checkMissiles();

    // TODO Real spawn system
    static int count = 0, lane = 0;
    count += 1;
    if(count >= 10)
    {
        count = 0;

        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
            lane++ % m_level->laneCount(), 0.5, EnemyShape::SQUARE_MIDDLE, m_level);
        m_entities.emplace_back(enemy);
        m_objects.emplace_back(enemy);
    }
}

void GameScene::checkEnemies()
{
    std::vector<std::shared_ptr<Entity>> removed;
    for (const auto& enemy : m_entities)
    {
        if (enemy->position() >= 100)
        {
            // TODO Do appropiate thing according to game rules
            
            removed.emplace_back(enemy);
        }
    }
    for(const auto& enemy : removed)
    {
        removeEntity(enemy);
    }
}

void GameScene::checkMissiles()
{
    // TODO
}
