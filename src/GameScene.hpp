#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.hpp"
#include "Bar.hpp"
#include "Player.hpp"
#include "InteractiveObjects.hpp"
#include "Map.hpp"

class GameScene : public Scene {
    public:
        GameScene() noexcept;
        void initialize(Game&) override;
        void update(Game&, float deltaTime) noexcept override;
        void draw(sf::RenderWindow&) noexcept override;

    private:
        Map m_map;
        Bar m_sanityBar;
        Bar m_dangerBar;
        Player m_player;
        InteractiveObjects m_objects;
};

#endif // GAMESCENE_H
