#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

class Game;

class InteractiveObject : public sf::Drawable {
    public:
        InteractiveObject();
        ~InteractiveObject();

        void update(Game&, float deltaTime) noexcept;

        void setPosition(float x, float y) noexcept;

        virtual void action() = 0;

    protected:
        AnimatedSprite m_sprite;

    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // INTERACTIVEOBJECT_H
