#include "Tileset.hpp"
#include "Game.hpp"

Tileset::Tileset() : m_columns(1), m_rows(1), m_scale(1.f) {
}

void Tileset::load(Game& game, const std::string& path, int columns, int rows) {
    m_tilesetTexture = game.getAssetCache().getTexture(path);
    m_columns = columns;
    m_rows = rows;

    auto tilesetBounds = m_tilesetTexture->getSize();
    m_tileBounds = sf::IntRect(0, 0, tilesetBounds.x / m_columns, tilesetBounds.y / m_rows);
}

void Tileset::setScale(float scale) noexcept {
    m_scale = scale;
}

unsigned int Tileset::getTileLength() noexcept {
    return m_tileBounds.width * m_scale;
}

sf::Sprite Tileset::getTile(int column, int row) noexcept {
    if (m_tilesetTexture->getSize().x == 0) {
        // Tileset texture not loaded yet
        return sf::Sprite();
    }

    sf::Sprite tileSprite;
    tileSprite.setTexture(*m_tilesetTexture);
    tileSprite.setScale(m_scale, m_scale);

    auto tileSpriteBounds = m_tileBounds;
    tileSpriteBounds.left = column * m_tileBounds.width;
    tileSpriteBounds.top = row * m_tileBounds.height;

    tileSprite.setTextureRect(tileSpriteBounds);

    return tileSprite;
}
