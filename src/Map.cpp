#include <fstream>
#include "Map.hpp"

void Map::initialize(Game& game) {
    m_tileset.load(game, "tileset.png", 4, 1);
    m_tileset.setScale(4.f);

    m_tileMappings[TileType::TileFloor] = std::make_pair<int, int>(0, 0);
    m_tileMappings[TileType::WoodFloor] = std::make_pair<int, int>(1, 0);
    m_tileMappings[TileType::Wall] = std::make_pair<int, int>(2, 0);
}

void Map::loadMap(const std::string& path) {
    parseMap(path);
    renderMap();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite tilesSprite;
    tilesSprite.setTexture(m_tilesTexture);
    target.draw(tilesSprite, states);
}

void Map::parseMap(const std::string& path) {
    std::ifstream file(path);
    if (file.is_open()) {
        file >> m_columns;
        file >> m_rows;

        for (unsigned int i = 0; i < m_columns * m_rows; i++) {
            unsigned int type;
            file >> type;
            m_tiles.push_back(static_cast<TileType>(type));
        }

        file.close();
    }
}

void Map::renderMap() {
    sf::RenderTexture tilesTexture;
    auto length = m_tileset.getTileLength();
    tilesTexture.create(length * m_columns, length * m_rows);

    for (unsigned int y = 0; y < m_rows; y++) {
        for (unsigned int x = 0; x < m_columns; x++) {
            auto type = m_tiles[y * m_columns + x];
            if (type == TileType::Nothing) {
                continue;
            }

            auto tc = m_tileMappings[type];
            sf::Sprite tileSprite = m_tileset.getTile(tc.first, tc.second);
            tileSprite.setPosition(x * length, y * length);
            tilesTexture.draw(tileSprite);
        }
    }

    tilesTexture.display();
    m_tilesTexture = tilesTexture.getTexture();
}
