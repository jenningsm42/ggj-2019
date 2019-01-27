#include "InteractiveObject.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

InteractiveObject::InteractiveObject() : m_activated(false) {
}

InteractiveObject::~InteractiveObject() {
}

void InteractiveObject::update(Game& game, Player& player, float deltaTime) noexcept {

    auto& input = game.getInputHandler();
    auto mouseWindowPosition = input.getMousePosition();
    auto mousePosition = game.getRenderWindow().mapPixelToCoords(mouseWindowPosition);

    auto pos = m_sprite.getPosition();
    auto bounds = m_sprite.getLocalBounds();
    auto playerPos = player.getPosition();
    auto playerBounds = player.getBounds();
    float dx = (pos.x + bounds.width / 2.f) - (playerPos.x + playerBounds.width / 2.f);
    float dy = (pos.y + bounds.height / 2.f) - (playerPos.y + playerBounds.height / 2.f);
    float distance2 = dx * dx + dy * dy;
    float r = player.getObjectRadius();
    bool inRadius = distance2 <= r * r;
    const float resetTime = 5; //in seconds

    if (m_sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !m_activated) {
        if (inRadius) {
            m_sprite.setColor(sf::Color::Green);
            if (input.getMouseTapped(sf::Mouse::Left)) {
                m_activated = true;
                action();
                auto t = clock.restart();

            }
        } else {
            m_sprite.setColor(sf::Color::Red);
        }
    } else {
        m_sprite.setColor(sf::Color::White);
    }


    float checkTime = clock.getElapsedTime().asSeconds();
    if (checkTime>resetTime){
        m_activated=false;
        reset();
    }

    m_sprite.update(deltaTime);
}

void InteractiveObject::setPosition(float x, float y) noexcept {
    auto bounds = m_sprite.getLocalBounds();
    m_sprite.setPosition(x, y - 2.f * (bounds.height - 32.f));
}

sf::Vector2f InteractiveObject::getPosition() noexcept {
    return m_sprite.getPosition();
}

void InteractiveObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
