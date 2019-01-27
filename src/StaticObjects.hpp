#ifndef STATICOBJECTS_H
#define STATICOBJECTS_H
#include <SFML/Graphics.hpp>

class Game;

class StaticObjects : public sf::Drawable {
    public:
        void add(Game&, const std::string& name, float x, float y);

    private:
        std::vector<sf::Sprite> m_objectSprites;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // STATICOBJECTS_H
