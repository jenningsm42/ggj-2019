//
// Created by Christian Wilkerson on 2019-01-26.
//

#include "NPC.hpp"

NPC::NPC(std::string inputName)
        : m_name(inputName),
          m_reactTimer(0.f),
          m_velocity(2.f),
          pastReact(nullptr)
{
// Nothing so far
}

void NPC::initialize(Game& game) noexcept {
    this->initReactions();

    auto& cache = game.getAssetCache();

    auto adventurerTexture = cache.getTexture("bandit.png");
    m_npcSprite.setTexture(*adventurerTexture);
    m_npcSprite.setGridSize(8, 7);

    auto spriteBounds = m_npcSprite.getLocalBounds();
    m_npcSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
    m_npcSprite.setScale(2.f, 2.f);

    m_npcSprite.setPosition(150, 250);

    m_npcSprite.addAnimation("idle", 0, 0, 4, 0.5f);
    m_npcSprite.addAnimation("run", 0, 1, 8, 0.15f);

    m_npcSprite.play("idle");

}

void NPC::update(Game& game, float deltaTime) noexcept {
    this->m_reactTimer += deltaTime;

    if (this->m_reactTimer >= 1.f and this->pastReact != nullptr) {
        this->react(this->pastReact, deltaTime);
    }

    auto currPos = m_npcSprite.getPosition();
    auto nextPos = sf::Vector2f(currPos.x * this->m_velocity, currPos.y * this->m_velocity);

    // Check map
    // If nextPos is object, turn
    // Else, go straight
    this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Straight, 7);
}

void NPC::react(std::shared_ptr<InteractiveObject> obj, float deltaTime) {
    this->pastReact = obj;

    auto shockType = obj->getType();
    auto currPos = m_npcSprite.getPosition();
    auto objPos = obj->getPosition();

    auto modX = abs(currPos.x - objPos.x);
    auto modY = abs(currPos.y - objPos.y);
    auto modifier = sqrtf(modX + modY);
    auto speed = modifier * this->m_reactSpeed[ObjectType::Door];

    if (this->m_reactTimer < 1.f) {
        this->m_reactTimer = 0.f;
        this->pathing(currPos.x, currPos.y, deltaTime, MovementType::SlowBack, 0.1f);
        return;
    }

    switch (shockType) {
        case ObjectType::Door:
            this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Scared, speed);
            break;
        default:
            // Should never get to here
            break;
    }
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(m_npcSprite);
}

void NPC::pathing(float xDir, float yDir, float deltaTime, MovementType react, float velocity) {
    int randX = rand()% -1 +1;
    int randY = rand()% -1 +1;

    if (xDir*randX == xDir) {
        randX = rand()% -1 +1;
    }

    if (yDir*randY == yDir) {
        randY = rand()% -1 +1;
    }

    switch(react) {
        //normal reaction
        case MovementType::Random:
            m_npcSprite.move(this->m_velocity*randX*deltaTime,this->m_velocity*randY*deltaTime);
            m_npcSprite.play("run");
            m_npcSprite.setScale(this->m_velocity * randX, this->m_velocity * randY);
            break;
            //scared reaction
        case MovementType::Scared:
            m_npcSprite.move(this->m_velocity*randX*deltaTime*velocity,this->m_velocity*randY*deltaTime*velocity);
            m_npcSprite.play("run");
            m_npcSprite.setScale(this->m_velocity * randX,this->m_velocity * randY);
            break;
            //cautious reaction just move back from object
        case MovementType::SlowBack:
            m_npcSprite.move(-this->m_velocity*deltaTime*velocity, -this->m_velocity*deltaTime*velocity);
            m_npcSprite.play("run");
            m_npcSprite.setScale(this->m_velocity,this->m_velocity);
            break;
            //go straight
        case MovementType::Straight:
            m_npcSprite.move(this->m_velocity*deltaTime*velocity,this->m_velocity*deltaTime*velocity);
            m_npcSprite.play("run");
            m_npcSprite.setScale(this->m_velocity,this->m_velocity);
        default:
            break;
    }
}

void NPC::initReactions() {
    this->m_reactSpeed[ObjectType::Door] = 1.3f;
}
