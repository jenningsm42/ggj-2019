#include "InteractiveSink.hpp"
#include "Game.hpp"

InteractiveSink::InteractiveSink(Game& game) {
    auto& cache = game.getAssetCache();
    auto texture = cache.getTexture("sink.png");
    auto sound = cache.getSoundBuffer("faucet.wav");
    m_sound.setBuffer(*sound);
    m_sprite.setTexture(*texture);

    m_sprite.setGridSize(4, 1);
    m_sprite.setScale(2.f, 2.f);

    m_sprite.addAnimation("off", 0, 0, 1, 1.f);
    m_sprite.addAnimation("on", 1, 0, 3, .2f);

    m_sprite.play("off");
}

ObjectType InteractiveSink::getType() const noexcept {
    return ObjectType::Sink;
}

void InteractiveSink::action() {
    m_sprite.play("on");
    m_sound.play();
}

void InteractiveSink::reset() {
    m_sprite.play("off");
    m_sound.stop();
}
