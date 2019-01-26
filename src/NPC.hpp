//
// Created by Christian Wilkerson on 2019-01-26.
//

#ifndef NPC_H
#define NPC_H

#include "Game.hpp"
#include "AnimatedSprite.hpp"
#include "InteractiveObject.hpp"

class NPC : public sf::Drawable {
public:
    NPC();

    void initialize (Game&) noexcept;
    void update (Game&, float deltaTime) noexcept;
    void react(std::shared_ptr<InteractiveObject> obj);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
    void pathing(float xDir, float yDir, float deltaTime, int react);

    AnimatedSprite m_sprite;
    std::string m_name;
};


#endif //GGJ2019_NPC_H
