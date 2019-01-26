#ifndef TILESET_H
#define TILESET_H
#include <memory>
#include <SFML/Graphics.hpp>

class Game;

class Tileset {
    public:
        Tileset();

        void load(Game& game, const std::string& path, int columns, int rows);

        void setScale(float scale) noexcept;
        unsigned int getTileLength() noexcept;

        sf::Sprite getTile(int column, int row) noexcept;

    private:
        std::shared_ptr<sf::Texture> m_tilesetTexture;
        sf::IntRect m_tileBounds;
        int m_columns;
        int m_rows;
        float m_scale;
};

#endif // TILESET_H
