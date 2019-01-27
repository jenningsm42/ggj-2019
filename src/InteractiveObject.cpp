#include "InteractiveObject.hpp"
#include "Game.hpp"

InteractiveObject::InteractiveObject() : m_activated(false) {
}

InteractiveObject::~InteractiveObject() {
}

void InteractiveObject::update(Game& game, float deltaTime) noexcept {
    auto& input = game.getInputHandler();
    auto mousePosition = input.getMousePosition();
    auto position = game.getRenderWindow().mapPixelToCoords(mousePosition);
    if (m_sprite.getGlobalBounds().contains(position.x, position.y) && !m_activated) {
        m_sprite.setColor(sf::Color::Green);
        if (input.getMouseTapped(sf::Mouse::Left)) {
            m_activated = true;
            action();
        }
    } else {
        m_sprite.setColor(sf::Color::White);
    }

    m_sprite.update(deltaTime);
}

void InteractiveObject::setPosition(float x, float y) noexcept {
    m_sprite.setPosition(x, y);
}

sf::Vector2f InteractiveObject::getPosition() noexcept {
    return m_sprite.getPosition();
}

void InteractiveObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
