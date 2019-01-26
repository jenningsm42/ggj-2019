#include "Map.hpp"
#include "StandardObject.hpp"

void Map::initialize(std::string path) {
    this->mapGrid = std::unordered_map<std::tuple<int, int>, StandardObject>();
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

            StandardObject obj = StandardObject();
            obj.initialize(val);
            obj.setPosition(x, y);
            mapGrid[std::make_tuple(x, y)] = obj;
        }

        file.close();
    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto e : mapGrid) {
        target.draw(e.second);
    }
}
