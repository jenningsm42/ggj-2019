#include "InteractiveObject.hpp"
#include "Game.hpp"

InteractiveObject::InteractiveObject(Game& game, const std::string& path) {
    auto& cache = game.getAssetCache();
    auto texture = cache.getTexture(path);
    m_sprite.setTexture(*texture);
    m_sprite.setScale(2.f, 2.f);
}

void InteractiveObject::update(Game& game, float) noexcept {
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
}

void InteractiveObject::setPosition(float x, float y) noexcept {
    m_sprite.setPosition(x, y);
}

void InteractiveObject::action() noexcept {
}

void InteractiveObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
