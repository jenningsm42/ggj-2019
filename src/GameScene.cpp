#include "GameScene.hpp"
#include "Game.hpp"
#include "InteractiveDoor.hpp"
#include "InteractiveStove.hpp"
#include "InteractiveSink.hpp"

GameScene::GameScene() noexcept
    : m_sanityBar("Sanity Bar"),
      m_dangerBar("Danger Bar"),
      m_npc("Joseph")
{
    this->m_sanityBar.setPosition(10, 500);
    this->m_dangerBar.setPosition(10, 450);
}

void GameScene::initialize(Game& game) {
    auto door = std::make_shared<InteractiveDoor>(game);
    door->setPosition(300.f, 50.f);
    m_objects.addObject(door);

    auto stove = std::make_shared<InteractiveStove>(game);
    stove->setPosition(300.f, 150.f);
    m_objects.addObject(stove);

    auto sink = std::make_shared<InteractiveSink>(game);
    sink->setPosition(364.f, 150.f);
    m_objects.addObject(sink);

    m_sanityBar.addToGui(game);
    m_dangerBar.addToGui(game);

    m_player.initialize(game, "Billy");

    m_sanityBar.addToGui(game);
    m_dangerBar.addToGui(game);

    m_map.initialize(game);
    m_map.loadMap("data/map.txt");

    m_npc.initialize(game);
}

void GameScene::update(Game& game, float deltaTime) noexcept {
    m_sanityBar.update(deltaTime / 2);
    m_dangerBar.update(deltaTime / 5);

    m_player.update(game, deltaTime);

    m_sanityBar.update(deltaTime / 2);
    m_dangerBar.update(deltaTime / 5);

    m_objects.update(game, deltaTime);

    m_npc.update(game, deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) noexcept {
    window.draw(m_map);
    window.draw(m_objects);
    window.draw(m_player);
    window.draw(m_npc);
}
