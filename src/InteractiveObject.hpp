#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <SFML/Audio.hpp>

class Game;
class Player;

enum struct ObjectType {
    Door,
    Stove,
    Sink
};

class InteractiveObject : public sf::Drawable {
    public:
        InteractiveObject();
        ~InteractiveObject();

        void update(Game&, Player& player, float deltaTime) noexcept;
        void setPosition(float x, float y) noexcept;

        virtual ObjectType getType() const noexcept = 0;
        sf::Vector2f getPosition() noexcept;

        virtual void action() = 0;
        virtual void reset() = 0;

    protected:
        AnimatedSprite m_sprite;
        sf::Sound m_sound;
        bool m_activated;
        sf::Clock clock;

    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // INTERACTIVEOBJECT_H
