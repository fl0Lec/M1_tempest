/**
 * @file scene.hpp
 * @brief Materialize the base of all scenes, e.g a menu, scoreboard or
 *  game screen
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <memory>
#include <vector>

#include "gameobject.hpp"
#include "entity.hpp"
#include "player.hpp"

namespace Engine
{

class Scene
    : public GameObject
{
public:
    Scene();

    virtual void update(const Input &in) override;
    virtual void render(const Output &out) const override;

    void createEnemy(Engine::EnemyShape type);

protected:
    /** List of objects that will be updated and rendered */
    std::vector<std::shared_ptr<GameObject>> m_objects;
    /** List of enemie object */
    std::vector<std::shared_ptr<Entity>> m_enemy;
    
    Player m_player;

};

};

#endif
