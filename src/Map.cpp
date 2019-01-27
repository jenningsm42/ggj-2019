#include <fstream>
#include "Map.hpp"

#include "InteractiveDoor.hpp"
#include "InteractiveStove.hpp"
#include "InteractiveSink.hpp"

void Map::initialize(Game& game) {
    m_tileset.load(game, "tileset.png", 4, 1);
    m_tileset.setScale(4.f);

    m_tileMappings[TileType::TileFloor] = std::make_pair<int, int>(0, 0);
    m_tileMappings[TileType::WoodFloor] = std::make_pair<int, int>(1, 0);
    m_tileMappings[TileType::Wall] = std::make_pair<int, int>(2, 0);
}

void Map::loadMap(Game& game, const std::string& path) {
    m_tiles.clear();
    m_collisionTiles.clear();

    parseMap(game, path);
    renderMap();
}

void Map::update(Game& game, float deltaTime) noexcept {
    m_objects.update(game, deltaTime);
}

bool Map::canPass(float x, float y) noexcept {
    int length = m_tileset.getTileLength();
    auto tileCoords = std::make_pair<int, int>(x / length, y / length);

    if (x < 0.f)
        tileCoords.first--;
    if (y < 0.f)
        tileCoords.second--;

    auto collisionIterator = m_collisionTiles.find(tileCoords);
    return collisionIterator == m_collisionTiles.end();
}

bool Map::isOutside(float x, float y) noexcept {
    int length = m_tileset.getTileLength();
    auto tileCoords = std::make_pair<int, int>(x / length, y / length);

    if (x < 0.f)
        tileCoords.first--;
    if (y < 0.f)
        tileCoords.second--;

    auto tileIt = m_mapTiles.find(tileCoords);
    return tileIt == m_mapTiles.end();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite tilesSprite;
    tilesSprite.setTexture(m_tilesTexture);
    target.draw(tilesSprite, states);

    target.draw(m_staticObjects, states);
    target.draw(m_objects, states);
}

void Map::parseMap(Game& game, const std::string& path) {
    std::ifstream file(path);
    if (file.is_open()) {
        file >> m_columns;
        file >> m_rows;

        for (unsigned int y = 0; y < m_rows; y++) {
            for (unsigned int x = 0; x < m_columns; x++) {
                unsigned int type;
                file >> type;
                m_tiles.push_back(static_cast<TileType>(type));

                auto key = std::make_pair<int, int>(x, y);
                if (m_tiles.back() == TileType::Wall) {
                    m_collisionTiles.emplace(std::move(key));
                }

                if (m_tiles.back() != TileType::Nothing) {
                    m_mapTiles.emplace(std::move(key));
                }
            }
        }

        int objectCount = 0;
        file >> objectCount;

        for (int i = 0; i < objectCount; i++) {
            std::string objectName = "";
            int tileX = 0, tileY = 0;

            file >> objectName;
            file >> tileX;
            file >> tileY;

            auto key = std::make_pair<int, int>(int(tileX), int(tileY));
            m_collisionTiles.emplace(std::move(key));

            float x = tileX * m_tileset.getTileLength();
            float y = tileY * m_tileset.getTileLength();

            if (objectName == "door") {
                auto door = std::make_shared<InteractiveDoor>(game);
                door->setPosition(x, y);
                m_objects.addObject(door);
            }
            else if (objectName == "stove") {
                auto stove = std::make_shared<InteractiveStove>(game);
                stove->setPosition(x, y);
                m_objects.addObject(stove);
            }
            else if (objectName == "sink") {
                auto sink = std::make_shared<InteractiveSink>(game);
                sink->setPosition(x, y);
                m_objects.addObject(sink);
            }
        }

        int staticObjectCount = 0;
        file >> staticObjectCount;

        for (int i = 0; i < staticObjectCount; i++) {
            std::string staticObjectName = "";
            int tileX = 0, tileY = 0;

            file >> staticObjectName;
            file >> tileX;
            file >> tileY;

            auto key = std::make_pair<int, int>(int(tileX), int(tileY));
            m_collisionTiles.emplace(std::move(key));

            float x = tileX * m_tileset.getTileLength();
            float y = tileY * m_tileset.getTileLength();

            m_staticObjects.add(game, staticObjectName, x, y);
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
