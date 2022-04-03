/**
 * @file gamescene.hpp
 * @brief Main scene for the game
 */

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "output.hpp"
#include "scene.hpp"

#include <memory>
#include <vector>

#include "entity.hpp"
#include "enemy.hpp"
#include "levelrenderer.hpp"
#include "player.hpp"

class GameScene
    : public Engine::Scene
{
public:
    GameScene(LevelType level);

    size_t nbLine() const;

    void createEnemy(EnemyShape type);

    virtual void update(const Engine::Input &in) override;
    virtual void render(const Engine::Output &out) const override;

private:
    std::shared_ptr<LevelRenderer> m_level;

    std::vector<std::shared_ptr<Enemy>> m_enemies;
    std::shared_ptr<Player> m_player;

};

#endif
