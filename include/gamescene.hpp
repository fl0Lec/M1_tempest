/**
 * @file gamescene.hpp
 * @brief Main scene for the game
 */

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "scene.hpp"

#include <memory>

#include "entity.hpp"
#include "enemy.hpp"
#include "levelrenderer.hpp"
#include "player.hpp"

class GameScene
    : public Engine::Scene
{
public:
    GameScene(LevelType level = TRIANGLE);

    void createEnemy(EnemyShape type);

private:
    std::shared_ptr<LevelRenderer> m_level;

    std::vector<std::shared_ptr<Entity>> m_enemy;
    std::shared_ptr<Player> m_player;

};

#endif
