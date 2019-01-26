//
// Created by Christian Wilkerson on 2019-01-26.
//

#include "NPC.hpp"

NPC::NPC() {

}

void NPC::initialize(Game& game) noexcept {

}

void NPC::update(Game& game, float deltaTime) noexcept {

}

void NPC::react(std::shared_ptr<InteractiveObject> obj) {

}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    // target.draw(m_sprite);
}

void NPC::pathing(float xDir, float yDir, float deltaTime, int react) {
    int randX = rand()% -1 +1;
    int randY = rand()% -1 +1;
    switch(react){
        //normal reaction
        case 1:
            m_sprite.move(xDir*randX*deltaTime,yDir*randY*deltaTime);
            m_sprite.play("run");
            m_sprite.setScale(2.f*randX,2.f*rand.Y);

        //scared reaction
        case 2:
            m_sprite.move(xDir*randX*deltaTime*3,yDir*randY*deltaTime*3);
            m_sprite.play("run");
            m_sprite.setScale(2.f*randX,2.f*rand.Y);

    }

}
