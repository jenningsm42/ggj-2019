#ifndef INTERACTIVEOBJECTS_H
#define INTERACTIVEOBJECTS_H
#include <memory>
#include "InteractiveObject.hpp"

class InteractiveObjects : public sf::Drawable {
    public:
        void addObject(std::shared_ptr<InteractiveObject> object);

        void update(Game& game, Player& player, float deltaTime) noexcept;

    private:
        std::vector<std::shared_ptr<InteractiveObject>> m_objects;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // INTERACTIVEOBJECTS_H
