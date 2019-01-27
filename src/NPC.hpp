//
// Created by Christian Wilkerson on 2019-01-26.
//

#ifndef NPC_H
#define NPC_H

#include "Game.hpp"
#include "AnimatedSprite.hpp"
#include "InteractiveObject.hpp"

enum struct MovementType {
    Straight,
    SlowBack,
    Random,
    Scared
};

class NPC : public sf::Drawable {
public:
    NPC(std::string inputName);

    void initialize (Game&) noexcept;
    void update (Game&, float deltaTime) noexcept;
    void react(std::shared_ptr<InteractiveObject> obj, float deltaTime);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
    void pathing(float xDir, float yDir, float deltaTime, MovementType react, float velocity);
    void initReactions();

    float m_velocity;
    std::string m_name;
    float m_reactTimer;
    AnimatedSprite m_npcSprite;
    std::shared_ptr<InteractiveObject> pastReact;
    std::unordered_map<ObjectType, float> m_reactSpeed;

};


#endif //GGJ2019_NPC_H
