
#include "gamescene.hpp"

#include <memory>
#include <vector>
#include <cstdlib>

#include "chooselevelscene.hpp"
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
    int lane = std::rand()%m_level->laneCount();
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
            lane++ % m_level->laneCount(), type, *m_level);

    m_enemies.emplace_back(enemy);
    m_objects.emplace_back(enemy);
}

std::shared_ptr<Enemy> GameScene::createEnemy(EnemyShape type, int lane, double position)
{
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
            lane % m_level->laneCount(), type, *m_level);
    enemy->m_position=position;

    return enemy;
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

    if(!m_lost && in.isKeyReleased(Keycode::KEY_F))
    {
        lose();
    }
    else if(m_lost && (in.isKeyPressed(KEY_SPACE) || in.isKeyReleased(KEY_ENTER)))
    {
        Game::instance()->setCurrentScene(
            std::shared_ptr<Scene>{new ChooseLevelScene{0}}
        );
    }

    m_spawnCounter += 1;
    if((m_spawnCounter > m_speedGen) && (std::rand() % 300 - m_spawnCounter > 0))
    {
        m_spawnCounter = 0;
        if (m_countBeforeIncrease)
            m_countBeforeIncrease--;
        else 
        {
            m_countBeforeIncrease = COUNT_BEFORE_INCREASE_SPEED;
            m_speedGen--;
        }
        int type = std::rand() % (EnemyShape::SPIKER+1);

        createEnemy(static_cast<EnemyShape>(type));
    }
}

void GameScene::checkEnemies()
{
    std::vector<std::shared_ptr<Entity>> removed;
    std::vector<std::shared_ptr<Enemy>> addedEnemies;
    for(const auto& enemy : m_enemies)
    {
        if(enemy->position() >= 100)
        {
            if (enemy->line()==m_player->line())
                lose();
            if (enemy->type()==SPIKER)
            {
                addedEnemies.emplace_back(createEnemy(FLIPPER, (enemy->line()+1)%m_level->laneCount(), 100));
                addedEnemies.emplace_back(createEnemy(FLIPPER, (enemy->line()==0?m_level->laneCount()-1:enemy->line()-1), 100));
            }
            removed.emplace_back(enemy);
        }
    }
    for(const auto& enemy : removed)
    {
        remove(enemy);
        m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), enemy),
            m_enemies.end());
    }
    for (auto& enemy : addedEnemies)
    {
        m_objects.emplace_back(enemy);
        m_enemies.emplace_back(enemy);
    }
}

void GameScene::checkMissiles()
{
    std::vector<std::shared_ptr<Enemy>> removedEnemies, addedEnemies;
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
                    if (enemy->type()==SPIKER)
                    {
                        addedEnemies.emplace_back(createEnemy(FLIPPER, (enemy->line()+1)%m_level->laneCount(), enemy->position()));
                        addedEnemies.emplace_back(createEnemy(FLIPPER, (enemy->line()==0?m_level->laneCount()-1:enemy->line()-1), enemy->position()));
                    }
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
    for (auto& enemy : addedEnemies)
    {
        m_objects.emplace_back(enemy);
        m_enemies.emplace_back(enemy);
    }
}

void GameScene::lose()
{
    if(!m_lost)
    {
        m_lost = true;

        remove(m_player);
        m_objects.emplace_back(std::shared_ptr<TextComponent>{
            new TextComponent{Game::instance()->center(), "GAME OVER", Color::RED}
        });
    }
}
