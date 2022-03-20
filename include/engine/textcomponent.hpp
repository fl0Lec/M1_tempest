/**
 * @file textcomponent.hpp
 * @brief Component to use in order to write text using Hershey font
 */

#ifndef __TEXTCOMPONENT_H__
#define __TEXTCOMPONENT_H__

#include <string>

#include "color.hpp"
#include "gameobject.hpp"
#include "hershey.hpp"
#include "vect2.hpp"

namespace Engine
{

class TextComponent
    : public GameObject
{
public:
    /**
     * @brief Construct a new Text Component object
     * 
     * @param center Position of the center of the text
     * @param text Text to be written
     * @param color Color to be use to draw text
     */
    TextComponent(const Vect2f & center, const std::string & text,
        const Color & color = Color::WHITE);

    /**
     * @brief Move the text to a new position
     * 
     * @param center New center position to move the text
     */
    void move(const Vect2f & center);

    /**
     * @brief Change the text currently written by the component
     * 
     * @param text Text to replace current one
     */
    void setText(const std::string & text);

    /**
     * @brief Change the color use to print the text
     * 
     * @param color Color to replace current one
     */
    void setColor(const Color & color);

    /**
     * @brief Get current starting position (left bottom) of the text
     */
    const Vect2f & position() const;

    /**
     * @brief Get current position of the center of the text
     */
    const Vect2f & center() const;

    /**
     * @brief Get current text printed by component
     */
    const std::string & text() const;

    /**
     * @brief Get current text color
     */
    const Color & color() const;

    virtual void update(const Input &in) override;
    virtual void render(const Output &out) const override;

    static const int INTER_LETTER_SPACE = 0;

protected:
    void computePosition();

private:
    Vect2f m_center;
    Vect2f m_position;
    std::string m_text;
    Color m_color;

};

};

#endif
