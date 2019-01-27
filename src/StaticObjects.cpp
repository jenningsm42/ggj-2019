#include "StaticObjects.hpp"
#include "Game.hpp"

void StaticObjects::add(Game& game, const std::string& name, float x, float y) {
    auto& cache = game.getAssetCache();
    auto path = name + ".png";
    auto texture = cache.getTexture(path);

    m_objectSprites.push_back(sf::Sprite());
    m_objectSprites.back().setTexture(*texture);
    m_objectSprites.back().setScale(2.f, 2.f);
    auto bounds = m_objectSprites.back().getLocalBounds();

    m_objectSprites.back().setPosition(x, y - 2.f * (bounds.height - 32.f));
}

void StaticObjects::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& object : m_objectSprites) {
        target.draw(object, states);
    }
}
