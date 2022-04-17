
#include "menuscene.hpp"
#include "keycode.hpp"
#include <algorithm>

using namespace Engine;

MenuScene::MenuScene()
    : m_selected{nullptr}, m_selectIterator{m_buttons.end()}
{ }

const std::vector<std::shared_ptr<Button>>& MenuScene::buttons() const
{
    return m_buttons;
}

void MenuScene::addButton(const std::shared_ptr<Button>& button)
{    
    resetSelection();
    m_buttons.push_back(button);
    m_selectIterator = m_buttons.end();

    button->setOnHoverAction([&](auto button){
        resetSelection();
        button->setSelected(true);
        m_selected = button;
    });
}

void MenuScene::removeButton(const std::shared_ptr<Button>& button)
{
    resetSelection();
    m_buttons.erase(std::find(m_buttons.begin(), m_buttons.end(), button),
        m_buttons.end());
    m_selectIterator = m_buttons.end();

    button->setOnHoverAction(nullptr);
}

void MenuScene::resetSelection()
{
    if(m_selected)
    {
        m_selected->setSelected(false);
        m_selected.reset();
    }
}

void MenuScene::update(const Input &in)
{
    for(const auto& button : m_buttons)
        button->update(in);

    const bool goLeft  = in.isKeyPressed(KEY_LEFT)  || in.isKeyPressed(KEY_Q);
    const bool goRight = in.isKeyPressed(KEY_RIGHT) || in.isKeyPressed(KEY_R);

    // Update selection with keyboard
    if(m_buttons.size() && (goLeft || goRight))
    {
        if(m_selectionDelay <= 0)
        {
            resetSelection();

            if(goLeft)
            {
                if(m_selectIterator == m_buttons.begin())
                    m_selectIterator = m_buttons.end();
                m_selectIterator--;
            }
            else if(goRight)
            {
                if(m_selectIterator == m_buttons.end()
                    || (++m_selectIterator) == m_buttons.end())
                    m_selectIterator = m_buttons.begin();
            }

            m_selected = *m_selectIterator;
            m_selected->setSelected(true);

            m_selectionDelay = SELECTION_CHANGE_DELAY;
        }
        else
            m_selectionDelay -= 1;
    }
    else if(m_selectionDelay > 0)
        m_selectionDelay = 0;

    if(m_selected &&
        (in.isKeyReleased(Keycode::KEY_SPACE) || in.isKeyReleased(Keycode::KEY_ENTER)))
    {
        m_selected->click();
    }
}

void MenuScene::render(const Output &out) const
{
    Scene::render(out);

    for(const auto& button : m_buttons)
        button->render(out);
}
