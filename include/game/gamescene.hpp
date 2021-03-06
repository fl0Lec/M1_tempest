/**
 * @file gamescene.hpp
 * @brief Main scene for the game
 */

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "scene.hpp"

#include <memory>
#include <random>
#include <vector>

#include "entity.hpp"
#include "enemy.hpp"
#include "levelrenderer.hpp"
#include "player.hpp"
#include "missile.hpp"
#include "output.hpp"
#include "textcomponent.hpp"

class GameScene
    : public Engine::Scene
{
public:
    GameScene(LevelType level);

    size_t nbLine() const;

    void createEnemy(EnemyShape type);
    std::shared_ptr<Enemy> createEnemy(EnemyShape type, int lane, double position);

    /**
     * @brief Add a missile to the scene
     */
    void addMissile(const std::shared_ptr<Missile>& missile);

    virtual void update(const Engine::Input &in) override;

protected:
    /** Check progression of enemies and react appropriately */
    void checkEnemies();

    /** Check the progression of missiles for any progression */
    void checkMissiles();

    /** Called when the player losses the game */
    void lose();

private:
    std::shared_ptr<LevelRenderer> m_level;

    std::vector<std::shared_ptr<Enemy>> m_enemies;
    std::vector<std::shared_ptr<Missile>> m_missiles;
    std::vector<std::shared_ptr<Missile>> m_newMissiles;

    std::shared_ptr<Player> m_player;

    unsigned int m_score;
    std::shared_ptr<Engine::TextComponent> m_scoreText;

    /** Spawn system */
    size_t m_spawnCounter = 0;
    const size_t COUNT_BEFORE_INCREASE_SPEED = 20;
    size_t m_countBeforeIncrease = COUNT_BEFORE_INCREASE_SPEED;
    size_t m_speedGen = 50;

    // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_randSpawn, m_randEnemy;

    bool m_lost = false;
};

#endif
