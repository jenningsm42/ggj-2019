#include "InteractiveStove.hpp"
#include "Game.hpp"

InteractiveStove::InteractiveStove(Game& game) {
    auto& cache = game.getAssetCache();
    auto texture = cache.getTexture("stove.png");
    auto sound = cache.getSoundBuffer("stove.wav");
    m_sound.setBuffer(*sound);
    m_sprite.setTexture(*texture);

    m_sprite.setGridSize(4, 1);
    m_sprite.setScale(2.f, 2.f);

    m_sprite.addAnimation("off", 0, 0, 1, 1.f);
    m_sprite.addAnimation("on", 1, 0, 3, .2f);

    m_sprite.play("off");
}

ObjectType InteractiveStove::getType() const noexcept {
    return ObjectType::Stove;
}

void InteractiveStove::action() {
    m_sprite.play("on");
    m_sound.play();
}

void InteractiveStove::reset() {{
    m_sprite.play("off");
    m_sound.stop();
}}
