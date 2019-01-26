//
// Created by Christian Wilkerson on 2019-01-26.
//

#include "NPC.hpp"

NPC::NPC(std::string inputName)
: m_name(inputName) {
    // Nothing so far
}

void NPC::initialize(Game& gamem, std::string inputName) noexcept {
    this->initReactions();

    auto& cache = game.getAssetCache();

    auto adventurerTexture = cache.getTexture("bandit.png");
    m_npcSprite.setTexture(*adventurerTexture);
    m_npcSprite.setGridSize(8, 7);

    auto spriteBounds = m_playerSprite.getLocalBounds();
    m_npcSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
    m_npcSprite.setScale(2.f, 2.f);

    m_npcSprite.setPosition(150, 250);

    m_npcSprite.addAnimation("idle", 0, 0, 4, 0.5f);
    m_npcSprite.addAnimation("run", 0, 1, 8, 0.15f);

    m_npcSprite.play("idle");

    this->m_name = inputName;
}

void NPC::update(Game& game, float deltaTime) noexcept {

}

void NPC::react(std::shared_ptr<InteractiveObject> obj, float deltaTime) {
    auto shockType = obj.getType();
    auto currPos = m_sprite.getPosition();
    auto objPos = obj.getPosition();

    auto modX = abs(currPos.x - objPos.x);
    auto modY = abs(currPos.y - objPos.y);

    auto modifier = sqrt(modX + modY);

    switch (shockType) {
        case ObjectType::Door:
            this.pathing(currPos.x, currPos.y, deltaTime, 2, modifier*this->m_reactSpeed(ObjectType::Door));
            break;
        default:
            // Should never get to here
            break;
    }
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    // target.draw(m_sprite);
}

void NPC::pathing(float xDir, float yDir, float deltaTime, int react, float velocity) {
    int randX = rand()% -1 +1;
    int randY = rand()% -1 +1;

    while(xDir*randX == xDir){
        randX = rand()% -1 +1;
    }
    else while(yDir*randY == yDir){
        randY = rand()% -1 +1;
    }
    switch(react){
        //normal reaction
        case 1:
            m_sprite.move(xDir*randX*deltaTime,yDir*randY*deltaTime);
            m_sprite.play("run");
            m_sprite.setScale(2.f*randX,2.f*rand.Y);

        //scared reaction
        case 2:
            m_sprite.move(xDir*randX*deltaTime*velocity,yDir*randY*deltaTime*3);
            m_sprite.play("run");
            m_sprite.setScale(2.f*randX,2.f*rand.Y);
    }
}

void NPC::initReactions() {
    this->m_reactSpeed.insert(ObjectType::Door, 1.3f);
}
