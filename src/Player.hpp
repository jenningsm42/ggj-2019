//
// Created by Christian Wilkerson on 2019-01-25.
//

#ifndef GGJ_2019_PLAYER_H
#define GGJ_2019_PLAYER_H


#include <SFML/Graphics/Drawable.hpp>
#include "Game.hpp"
#include "Map.hpp"

class Player : public sf::Drawable{
public:
    Player();

    void initialize(Game&, std::string name);
    void update(Game&, Map&, float deltaTime) noexcept;
    void setName(std::string);
    std::string getName();

private:
    const int sprintConst;
    void setXDirection(float dir);
    float getXDirection();

    AnimatedSprite m_playerSprite;
    std::string m_name;
    float m_currentXDirection;
    int sprintLevel;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const noexcept;
};


#endif //GGJ_2019_PLAYER_H
