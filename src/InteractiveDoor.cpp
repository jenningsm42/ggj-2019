#include "InteractiveDoor.hpp"
#include "Game.hpp"

InteractiveDoor::InteractiveDoor(Game& game) {
    auto& cache = game.getAssetCache();
    auto texture = cache.getTexture("door.png");
    m_sprite.setTexture(*texture);

    m_sprite.setGridSize(8, 8);
    m_sprite.setScale(2.f, 2.f);

    m_sprite.addAnimation("closed", 0, 0, 1, 1.f);
    m_sprite.addAnimation("opening", 1, 0, 2, .3f);
    m_sprite.addAnimation("open", 2, 0, 1, 1.f);
}

ObjectType InteractiveDoor::getType() const noexcept {
    return ObjectType::Door;
}

void InteractiveDoor::action() {
    m_sprite.play("opening");
    m_sprite.playAfter("open");
}

void InteractiveDoor::reset() {{
    m_sprite.play("closed");
}}
