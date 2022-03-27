
#include "scene.hpp"
#include "enemy.hpp"

#include <memory>

using namespace Engine;

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
