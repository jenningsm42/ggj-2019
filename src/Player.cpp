//
// Created by Christian Wilkerson on 2019-01-25.
//

#include "Player.hpp"
#include <cmath>

Player::Player() : sprintConst(1000), m_currentXDirection(2.f), sprintLevel(sprintConst) {
}

void Player::initialize(Game& game, std::string name) {
    auto& cache = game.getAssetCache();

    auto adventurerTexture = cache.getTexture("bandit.png");
    m_playerSprite.setTexture(*adventurerTexture);
    m_playerSprite.setGridSize(8, 7);
    auto spriteBounds = m_playerSprite.getLocalBounds();
    m_playerSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
    m_playerSprite.setScale(2.f, 2.f);

    m_playerSprite.setPosition(500, 200);

    m_playerSprite.addAnimation("idle", 0, 0, 4, 0.5f);
    m_playerSprite.addAnimation("run", 0, 1, 8, 0.15f);

    m_playerSprite.play("idle");

    this->setName(name);
}

void Player::update(Game& game, Map& map, float deltaTime) noexcept{
    m_playerSprite.update(deltaTime);

    auto& input = game.getInputHandler();

    const bool movingLeft = input.getKeyDown(sf::Keyboard::A);
    const bool movingRight = input.getKeyDown(sf::Keyboard::D);
    const bool movingUp = input.getKeyDown(sf::Keyboard::W);
    const bool movingDown = input.getKeyDown(sf::Keyboard::S);
    const bool sprint = input.getKeyDown(sf::Keyboard::LShift);


    const float speed = 280.f;
    float velX = 0.f;
    float velY = 0.f;

    if (movingLeft && !movingRight){
        velX = -speed;
        if(sprint&&sprintLevel>10){
            velX *= 2.f;
            m_playerSprite.play("run");
            if(sprintLevel>0){
                sprintLevel-=2;
            }
        }
        else if(sprintLevel<10 || !sprint){
            m_playerSprite.play("run");
            if(sprintLevel<sprintConst){
                sprintLevel++;
            }
        } else {
            velX *= .5f;
        }
        m_playerSprite.setScale(2.f,2.f);
        setXDirection(2.f);
    }
    else if(movingRight && !movingLeft){
        velX = speed;
        if(sprint&&sprintLevel>10){
            velX *= 2.f;
            m_playerSprite.play("run");
            if(sprintLevel>0){
                sprintLevel-=2;
            }
        }
        else if(sprintLevel<10 || !sprint){
            m_playerSprite.play("run");
            if(sprintLevel<sprintConst){
                sprintLevel++;
            }
        } else {
            velX *= .5f;
        }

        m_playerSprite.setScale(-2.f,2.f);
        setXDirection(-2.f);
    }
    else if (!movingLeft && !movingRight){
        m_playerSprite.play("run");
    }

    if(movingUp && !movingDown){
        velY = -speed;
        if(sprint && sprintLevel>10){
            velY *= 2.f;
            m_playerSprite.play("run");
            if(sprintLevel>0){
                sprintLevel-=2;
            }
            }
        else if(sprintLevel<10 || !sprint){
            m_playerSprite.play("run");
            if(sprintLevel<sprintConst){
                sprintLevel++;
            }
        } else {
            velY *= .5f;
        }

        m_playerSprite.setScale(getXDirection(),2.f);
    }
    else if(movingDown && !movingUp){
        velY = speed;
        if(sprint && sprintLevel>10){
            velY *= 3.f;
            m_playerSprite.play("run");
            if(sprintLevel>0){
                sprintLevel-=2;
            }
            }
        else if(sprintLevel<10 || !sprint){
            m_playerSprite.play("run");
            if(sprintLevel<sprintConst){
                sprintLevel++;
            }
        } else {
            velY *= .5f;
        }

        m_playerSprite.setScale(getXDirection(),2.f);
    }
    else if(!movingDown && !movingUp){
        m_playerSprite.play("run");
    }

    if(!movingDown && !movingUp && !movingLeft && !movingRight){
        m_playerSprite.play("idle");
    }

    if(velX!=0 && velY!=0){
        velX=velX/sqrtf(2);
        velY=velY/sqrtf(2);
    }

    m_playerSprite.move(velX * deltaTime, 0.f);
    auto bounds = m_playerSprite.getGlobalBounds();

    if (map.isOutside(bounds.left, bounds.top) ||
        map.isOutside(bounds.left, bounds.top + bounds.height) ||
        map.isOutside(bounds.left + bounds.width, bounds.top) ||
        map.isOutside(bounds.left + bounds.width, bounds.top + bounds.height)
    ) {
        m_playerSprite.move(-velX * deltaTime, 0.f);
    }

    if (!map.canPass(bounds.left, bounds.top) ||
        !map.canPass(bounds.left, bounds.top + bounds.height) ||
        !map.canPass(bounds.left + bounds.width, bounds.top) ||
        !map.canPass(bounds.left + bounds.width, bounds.top + bounds.height)
    ) {
        m_playerSprite.move(-velX * deltaTime * .5f, 0.f);
    }

    m_playerSprite.move(0.f, velY * deltaTime);
    bounds = m_playerSprite.getGlobalBounds();

    if (map.isOutside(bounds.left, bounds.top) ||
        map.isOutside(bounds.left, bounds.top + bounds.height) ||
        map.isOutside(bounds.left + bounds.width, bounds.top) ||
        map.isOutside(bounds.left + bounds.width, bounds.top + bounds.height)
    ) {
        m_playerSprite.move(0.f, -velY * deltaTime);
    }

    if (!map.canPass(bounds.left, bounds.top) ||
        !map.canPass(bounds.left, bounds.top + bounds.height) ||
        !map.canPass(bounds.left + bounds.width, bounds.top) ||
        !map.canPass(bounds.left + bounds.width, bounds.top + bounds.height)
    ) {
        m_playerSprite.move(0.f, -velY * deltaTime * .5f);
    }

    m_playerSprite.update(deltaTime);

    auto view = game.getRenderWindow().getView();
    view.setCenter(m_playerSprite.getPosition());
    game.getRenderWindow().setView(view);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept {
    target.draw(m_playerSprite, states);
}



float Player::getXDirection() {
    return this->m_currentXDirection;
}

void Player::setXDirection(float dir) {
    this->m_currentXDirection = dir;
}

std::string Player::getName() {
    return this->m_name;
}

void Player::setName(std::string name) {
    this->m_name=name;
}
