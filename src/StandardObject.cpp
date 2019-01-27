//
// Created by Benjamin Lang on 2019-01-26.
//

#include "StandardObject.hpp"
#include "Game.hpp"

StandardObject::StandardObject() {
}

StandardObject::~StandardObject() {
}

void StandardObject::initialize(int type) {
    sf::Texture texture = sf::Texture();
    switch (type) {
        case StandardObjectType::Stove: {
            texture.loadFromFile("../data/stove.png");
        } break;
        case StandardObjectType::Sink: {
            texture.loadFromFile("../data/Sink.png");
        } break;
        default: {
            texture.loadFromFile("../data/floor.png");
        }
    }
    m_sprite = sf::Sprite(texture);
}

void StandardObject::setPosition(float x, float y) noexcept {
    m_sprite.setPosition(x, y);
}

sf::Vector2f StandardObject::getPosition() noexcept {
    return m_sprite.getPosition();
}

void StandardObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}


