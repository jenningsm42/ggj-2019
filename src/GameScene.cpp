#include "GameScene.hpp"
#include "Game.hpp"

GameScene::GameScene() noexcept
    : m_sanityBar("Sanity Bar"),
      m_dangerBar("Danger Bar"),
      m_npc("Joseph")
{
    this->m_sanityBar.setPosition(10, 500);
    this->m_dangerBar.setPosition(10, 450);
}

void GameScene::initialize(Game& game) {
    m_sanityBar.addToGui(game);
    m_dangerBar.addToGui(game);

    m_player.initialize(game, "Billy");

    m_sanityBar.addToGui(game);
    m_dangerBar.addToGui(game);

    m_map.initialize(game);
    m_map.loadMap(game, "data/map.txt");

    m_npc.initialize(game);
}

void GameScene::update(Game& game, float deltaTime) noexcept {
    m_sanityBar.update(deltaTime / 2);
    m_dangerBar.update(deltaTime / 5);

    m_player.update(game, m_map, deltaTime);

    m_sanityBar.update(deltaTime / 2);
    m_dangerBar.update(deltaTime / 5);

    m_map.update(game, m_player, deltaTime);

    m_npc.update(game, deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) noexcept {
    window.draw(m_map);
    window.draw(m_player);
    window.draw(m_npc);
}
