/**
 * @file menuscene.hpp
 * @brief Scene that represents a menu with buttons to choose options
 */

#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "scene.hpp"

#include <memory>
#include <vector>

#include "button.hpp"

namespace Engine
{

class MenuScene
    : public Scene
{
public:
    MenuScene();

    const std::vector<std::shared_ptr<Button>>& buttons() const;

    void addButton(const std::shared_ptr<Button>& button);
    void removeButton(const std::shared_ptr<Button>& button);

    void resetSelection();

    virtual void update(const Input &in) override;
    virtual void render(const Output &out) const override;

private:
    std::vector<std::shared_ptr<Button>> m_buttons;
    std::shared_ptr<Button> m_selected;
    std::vector<std::shared_ptr<Button>>::iterator m_selectIterator;

    int m_selectionDelay = 0;

    /** How many updates before the next button is selected, if a key is still
        pressed */
    static const int SELECTION_CHANGE_DELAY = 10;

};

};

#endif
