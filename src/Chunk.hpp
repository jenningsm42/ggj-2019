#ifndef CHUNK_H
#define CHUNK_H
#include <SFML/Graphics.hpp>
#include "Tileset.hpp"

class Chunk : public sf::Drawable {
    public:
        /* Chunk initializes to given chunk coordinates */
        Chunk(Tileset&, int x, int y);

        bool intersectsView(const sf::RenderTarget&) const noexcept;

        static const int tileCount = 16; // 16x16 tiles

    private:
        uint8_t m_tileType[tileCount][tileCount];
        sf::FloatRect m_bounds;

        // In chunk coordinates
        int m_x;
        int m_y;

        sf::Texture m_texture;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

        void generate() noexcept;
        void render(Tileset&);
};

#endif // CHUNK_H
