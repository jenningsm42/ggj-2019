#ifndef MAP_H
#define MAP_H
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Tileset.hpp"

enum struct TileType : unsigned int {
    Nothing = 0,
    TileFloor = 1,
    WoodFloor = 2,
    Wall = 3,
};

class Map : public sf::Drawable {
    public:
        void initialize(Game& game);

        void loadMap(const std::string& path);

    private:
        Tileset m_tileset;
        std::vector<TileType> m_tiles;
        std::unordered_map<TileType, std::pair<int, int>> m_tileMappings;
        unsigned int m_columns;
        unsigned int m_rows;
        sf::Texture m_tilesTexture;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

        void parseMap(const std::string& path);
        void renderMap();
};

#endif // MAP_H
