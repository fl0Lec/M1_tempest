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
    virtual void update(const Input &in) override;
    virtual void render(const Output &out) const override;

protected:
    void remove(const std::shared_ptr<GameObject>& obj);

    /** List of objects that will be updated and rendered */
    std::vector<std::shared_ptr<GameObject>> m_objects;

};

};

#endif
