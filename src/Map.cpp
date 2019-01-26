#include "Map.hpp"

void Map::initialize(std::string path) {
    this->mapGrid = std::unordered_map<std::tuple<int, int>, int>();
    std::ifstream file;
    file.open(path);
    if (file.good()) {

        file >> this->length;
        file >> this->width;

        int val;
        int x;
        int y;
        while (file >> val) {
            file >> x;
            file >> y;
            mapGrid[std::make_tuple(x, y)] = val;
        }

        file.close();
    }
}

void Map::draw(sf::RenderWindow& window) noexcept {
    window.draw(m_sprite);
}
