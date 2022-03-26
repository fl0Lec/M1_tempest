
#include "scene.hpp"
#include "enemy.hpp"

using namespace Engine;

void Scene::createEnemy(EnemyShape type)
{
    // TO DO
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
