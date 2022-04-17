/**
 * @file button.hpp
 * @brief Describe a button on which a user can click
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "gameobject.hpp"

#include <functional>
#include <memory>
#include <string>

#include "color.hpp"
#include "textcomponent.hpp"
#include "vect2.hpp"

namespace Engine
{

class Button;

using Callback = std::function<void(const std::shared_ptr<Button>&)>;

class Button
    : public GameObject
{
public:
    Button(const Vect2f& pos, const Vect2f& size, const std::string& text,
        Callback onClick = nullptr, Callback onHover = nullptr);

    const Vect2f& pos() const;
    const Vect2f& size() const;
    const std::string& text() const;

    bool isSelected() const;
    bool isPressed() const;
    
    void setPos(const Vect2f& pos);
    void setSize(const Vect2f& size);
    void setText(const std::string& text);

    void setSelected(bool isSelected);

    void setOnClickAction(Callback onClick);
    void setOnHoverAction(Callback onHover);

    void click();

    // To create a shared_ptr on this that do not call delete: 
    //  as we are not permitted to use raw pointer, and this is not a
    //  shared_ptr itself
    std::shared_ptr<Button> thisShared();

    virtual void update(const Input &in) override;
    virtual void render(const Output &out) const override;
    
private:
    Vect2f m_pos, m_size;
    bool m_isSelected = false, m_isPressed = false, m_isHovered = false;

    Callback m_onClick, m_onHover;

    std::shared_ptr<TextComponent> m_text;

    static const Color SELECTED_COLOR, PRESSED_COLOR;

};

};

#endif
