#include <random>
#include "Chunk.hpp"

Chunk::Chunk(Tileset& tileset, int x, int y) : m_x(x), m_y(y) {
    const int length = tileCount * tileset.getTileLength();
    m_bounds.left = x * length;
    m_bounds.top = y * length;
    m_bounds.width = length;
    m_bounds.height = length;

    generate();
    render(tileset);
}

bool Chunk::intersectsView(const sf::RenderTarget& target) const noexcept {
    auto view = target.getView();
    auto center = view.getCenter();
    auto size = view.getSize();

    sf::FloatRect targetBounds(
        center.x - size.x / 2.f,
        center.y - size.y / 2.f,
        size.x,
        size.y);

    return targetBounds.intersects(m_bounds);
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setPosition(m_bounds.left, m_bounds.top);
    target.draw(sprite, states);
}

void Chunk::generate() noexcept {
    std::mt19937 generator(m_x * m_y + (m_x >> 16));
    std::uniform_int_distribution<int> distribution(0, 6);

    for (int x = 0; x < tileCount; x++) {
        for (int y = 0; y < tileCount; y++) {
            m_tileType[x][y] = distribution(generator);
        }
    }
}

void Chunk::render(Tileset& tileset) {
    const int length = tileCount * tileset.getTileLength();
    sf::RenderTexture renderTexture;
    renderTexture.create(length, length);

    for (int x = 0; x < tileCount; x++) {
        for (int y = 0; y < tileCount; y++) {
            auto tileSprite = tileset.getTile(1 + m_tileType[x][y], 0);
            tileSprite.setPosition(x * tileset.getTileLength(), y * tileset.getTileLength());
            renderTexture.draw(tileSprite);
        }
    }

    renderTexture.display();
    m_texture = renderTexture.getTexture();
}
