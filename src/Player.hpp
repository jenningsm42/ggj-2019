//
// Created by Christian Wilkerson on 2019-01-25.
//

#ifndef GGJ_2019_PLAYER_H
#define GGJ_2019_PLAYER_H


#include <SFML/Graphics/Drawable.hpp>
#include "Game.hpp"
#include "AnimatedSprite.hpp"

class Player : public sf::Drawable{
public:
    Player();

    void initialize(Game&, std::string name);
    void update(Game&, float deltaTime) noexcept;
    void setName(std::string);
    std::string getName();




private:
    AnimatedSprite m_playerSprite;
    std::string m_name;
    float m_currentXDirection;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const noexcept;
    int sprintLevel;
    const int sprintConst = 1000;
    void setXDirection(float dir);
    float getXDirection();

};


#endif //GGJ_2019_PLAYER_H
