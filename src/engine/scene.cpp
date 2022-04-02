
#include "scene.hpp"
#include "enemy.hpp"

#include <memory>

using namespace Engine;

void Scene::remove(const std::shared_ptr<GameObject>& obj)
{
    m_objects.erase(
        std::remove(m_objects.begin(), m_objects.end(), obj),
        m_objects.end()
    );
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
