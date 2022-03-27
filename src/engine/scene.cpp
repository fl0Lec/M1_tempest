
#include "scene.hpp"
#include "enemy.hpp"

#include <memory>

using namespace Engine;

Scene::Scene(): m_player()
{

}

void Scene::createEnemy(EnemyShape type)
{
    //TO UPGRADE where enemy (random)
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(1, 1.2, type);
    m_enemy.emplace_back(enemy);
}

void Scene::update(const Input &in)
{
    for(auto& obj : m_objects)
        obj->update(in);
}

void Scene::render(const Output &out) const
{
    for(auto& obj : m_objects)
        obj->render(out);
}
