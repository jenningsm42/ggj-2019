#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.hpp"
#include "AnimatedSprite.hpp"

#include "Bar.hpp"

#include "Player.hpp"


class GameScene : public Scene {
    public:
        GameScene() noexcept;
        void initialize(Game&) override;
        void update(Game&, float deltaTime) noexcept override;
        void draw(sf::RenderWindow&) noexcept override;

    private:
        sf::Text m_text;
        Bar m_sanityBar;
        Bar m_dangerBar;
        AnimatedSprite m_sprite;
        Player m_player;
};

#endif // GAMESCENE_H
