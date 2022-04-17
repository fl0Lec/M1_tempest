
#include "gamescene.hpp"

#include <memory>
#include <vector>

#include "enemy.hpp"
#include "game.hpp"
#include "missile.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "textcomponent.hpp"

using namespace Engine;

GameScene::GameScene(LevelType level)
    : m_level{
        new LevelRenderer{
            Game::instance()->center()
                - Vect2f{0, Game::instance()->height() / 15.0f},
            Game::instance()->height(),
            level
        }},
        m_player(new Player{*m_level, *this}),
        m_score{0},
        m_scoreText{new TextComponent{
            Game::instance()->center()
                + Vect2f{0, Game::instance()->height() * 2.0f / 5.0f},
            "Score: 0", Color::BLUE
        }}
{
    // Insert level first to be in background, if not we should render it manually
    m_objects.emplace_back(m_level);
    m_objects.emplace_back(m_scoreText);

    m_objects.emplace_back(m_player);

    createEnemy(SQUARE_MIDDLE);
}

void GameScene::createEnemy(EnemyShape type)
{
    //TO UPGRADE where enemy (random)
    static int lane = 0;
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
            lane++ % m_level->laneCount(), 0.5, EnemyShape::SQUARE_MIDDLE, *m_level);

    m_enemies.emplace_back(enemy);
    m_objects.emplace_back(enemy);
}

void GameScene::addMissile(const std::shared_ptr<Missile>& missile)
{
    m_newMissiles.emplace_back(missile);
}

size_t GameScene::nbLine() const
{
    return m_level->laneCount();
}

void GameScene::update(const Engine::Input &in)
{
    Engine::Scene::update(in);

    if(m_newMissiles.size())
    {
        for(const auto& missile : m_newMissiles)
        {
            m_missiles.emplace_back(missile);
            m_objects.emplace_back(missile);
        }
        m_newMissiles.clear();
    }
    
    checkEnemies();
    checkMissiles();

    // TODO Real spawn system
    static int count = 0;
    count += 1;
    if(count >= 10)
    {
        count = 0;

        // TODO Remove shape
        createEnemy(EnemyShape::SQUARE_MIDDLE);
    }
}

void GameScene::checkEnemies()
{
    std::vector<std::shared_ptr<Entity>> removed;
    for(const auto& enemy : m_enemies)
    {
        if(enemy->position() >= 100)
        {
            // TODO Do appropiate thing according to game rules
            
            removed.emplace_back(enemy);
        }
    }
    for(const auto& enemy : removed)
    {
        remove(enemy);
        m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), enemy),
            m_enemies.end());
    }
}

void GameScene::checkMissiles()
{
    std::vector<std::shared_ptr<Enemy>> removedEnemies;
    std::vector<std::shared_ptr<Missile>> removedMissiles;
    for(const auto& missile : m_missiles)
    {
        if(missile->position() < 0.0f)
        {
            removedMissiles.emplace_back(missile);
        }
        else
        {
            for(const auto& enemy : m_enemies)
            {
                if(enemy->line() == missile->line()
                    && enemy->position() > missile->position() - Missile::WIDTH / 2
                    && enemy->position() < missile->position() + Missile::WIDTH / 2)
                {
                    removedEnemies.emplace_back(enemy);
                    removedMissiles.emplace_back(missile);

                    m_score += enemy->givenScore();
                    m_scoreText->setText("Score: " + std::to_string(m_score));
                }
            }
        }
    }

    for(const auto& enemy : removedEnemies)
    {
        remove(enemy);
        m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), enemy),
            m_enemies.end());
    }
    for(const auto& missile : removedMissiles)
    {
        remove(missile);
        m_missiles.erase(std::remove(m_missiles.begin(), m_missiles.end(), missile),
            m_missiles.end());
    }
}
