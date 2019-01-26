#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

class Game;

class InteractiveObject : public sf::Drawable {
    public:
        InteractiveObject(Game&, const std::string& path);
        void update(Game&, float deltaTime) noexcept;

        void setPosition(float x, float y) noexcept;

        void action() noexcept;

    private:
        AnimatedSprite m_sprite;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // INTERACTIVEOBJECT_H
