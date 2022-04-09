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

    /**
     * @brief Add/Remove an entity from the scene
     * 
     * @param entity Entity to be added/removed
     */
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);

    virtual void update(const Engine::Input &in) override;

protected:
    /** Check progression of enemies and react appropriately */
    void checkEnemies();

    /** Check the progression of missiles for any progression */
    void checkMissiles();

private:
    std::shared_ptr<LevelRenderer> m_level;

    std::vector<std::shared_ptr<Entity>> m_entities;
    std::shared_ptr<Player> m_player;

};

#endif
