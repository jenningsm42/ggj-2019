//
// Created by Benjamin Lang on 2019-01-26.
//

#ifndef GGJ2019_STANDARDOBJECT_H
#define GGJ2019_STANDARDOBJECT_H

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

class Game;

enum StandardObjectType  {
    Stove = 0,
    Sink,
    Wall
};

class StandardObject : public sf::Drawable {
public:
    StandardObject();
    ~StandardObject();

    void initialize(int type);
    void setPosition(float x, float y) noexcept;
    sf::Vector2f getPosition() noexcept;


protected:
    sf::Sprite m_sprite;

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif //GGJ2019_STANDARDOBJECT_H
