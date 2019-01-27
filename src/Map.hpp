#ifndef MAP_H
#define MAP_H
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Tileset.hpp"
#include "InteractiveObjects.hpp"

enum struct TileType : unsigned int {
    Nothing = 0,
    TileFloor = 1,
    WoodFloor = 2,
    Wall = 3,
};

class Map : public sf::Drawable {
    public:
        void initialize(Game& game);

        void loadMap(Game& game, const std::string& path);

        void update(Game&, float deltaTime) noexcept;

    private:
        Tileset m_tileset;
        std::vector<TileType> m_tiles;
        std::unordered_map<TileType, std::pair<int, int>> m_tileMappings;
        unsigned int m_columns;
        unsigned int m_rows;
        sf::Texture m_tilesTexture;

        InteractiveObjects m_objects;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

        void parseMap(Game& game, const std::string& path);
        void renderMap();
};

#endif // MAP_H
