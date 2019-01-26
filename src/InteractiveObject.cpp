#include "InteractiveObject.hpp"
#include "Game.hpp"

InteractiveObject::InteractiveObject() {
}

InteractiveObject::~InteractiveObject() {
}

void InteractiveObject::update(Game& game, float deltaTime) noexcept {
    auto& input = game.getInputHandler();
    auto position = input.getMousePosition();
    if (m_sprite.getGlobalBounds().contains(position.x, position.y)) {
        m_sprite.setColor(sf::Color::Yellow);
        if (input.getMouseTapped(sf::Mouse::Left)) {
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
