#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.hpp"
#include "AnimatedSprite.hpp"
#include "Bar.hpp"

class GameScene : public Scene {
    public:
        void initialize(Game&) override;
        void update(Game&, float deltaTime) noexcept override;
        void draw(sf::RenderWindow&) noexcept override;

    private:
        sf::Text m_text;
        Bar *m_sanityBar;
        AnimatedSprite m_sprite;
};

#endif // GAMESCENE_H
