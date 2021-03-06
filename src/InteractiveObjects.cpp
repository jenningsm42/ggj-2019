#include "InteractiveObjects.hpp"

void InteractiveObjects::addObject(std::shared_ptr<InteractiveObject> object) {
    m_objects.push_back(object);
}

void InteractiveObjects::update(Game& game, Player& player, float deltaTime) noexcept {
    for (auto& object : m_objects) {
        object->update(game, player, deltaTime);
    }
}

void InteractiveObjects::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& object : m_objects) {
        target.draw(*object, states);
    }
}
