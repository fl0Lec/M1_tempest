
#include "gamescene.hpp"

#include "game.hpp"
#include "player.hpp"

GameScene::GameScene(LevelType level)
    : m_level(new LevelRenderer{Engine::Game::instance()->center(), level}),
        m_player(new Player{})
{
    // Insert level first to be in background, if not we should render it manually
    m_objects.emplace_back(m_level);

    m_objects.emplace_back(m_player);
}

void GameScene::createEnemy(EnemyShape type)
{
    //TO UPGRADE where enemy (random)
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(0, 0.5, type);
    m_enemy.emplace_back(enemy);
    m_objects.emplace_back(enemy);
}

size_t GameScene::getNbLine() const
{
    return m_level->laneCount();
}

 void GameScene::update(const Engine::Input &in)
 {
    Engine::Scene::update(in);
    m_level->clearEnemy();
    for (auto& e : m_enemy)
    {
        m_level->drawEnemy(e);
    }
 }