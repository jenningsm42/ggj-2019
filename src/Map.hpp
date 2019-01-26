#ifndef MAP_H
#define MAP_H
#include <random>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <tuple>
#include <iostream>
#include "StandardObject.hpp"

class Map : public sf::Drawable {
    public:
        void initialize(std::string path);
        void update() noexcept;

    private:
        std::unordered_map<std::tuple<int, int>, StandardObject> mapGrid;
        int length;
        int width;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // MAP_H
