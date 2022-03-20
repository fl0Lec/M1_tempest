
#include "bnojourscene.hpp"
#include "textcomponent.hpp"

using namespace Engine;

BnojourScene::BnojourScene()
    : m_text(new TextComponent{Vect2f{10,10}, "Bnojour"})
{
    m_objects.emplace_back(m_text);
}

void BnojourScene::update(const Engine::Input &in)
{
    m_text->move(in.mousePosition());
}
