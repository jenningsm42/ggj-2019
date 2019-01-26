#ifndef MAP_H
#define MAP_H
#include <random>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <tuple>
#include <iostream>

class Map : public sf::Drawable {
    public:
        void initialize(std::string path);
        void update() noexcept;

    private:
        std::unordered_map<std::tuple<int, int>, int> mapGrid;
        int length;
        int width;
        void draw(sf::RenderWindow&) noexcept override;
};

#endif // MAP_H
