#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite() : m_currentAnimationName(""), m_nextAnimationName("") {
    m_currentColumn = 0;
    m_currentRow = 0;
    m_currentFrameTime = 0.f;
}

void AnimatedSprite::setGridSize(int columns, int rows) noexcept {
    m_columns = columns;
    m_rows = rows;

    auto textureSize = getTexture()->getSize();
    m_spriteRectangle.width = textureSize.x / columns;
    m_spriteRectangle.height = textureSize.y / rows;

    m_spriteRectangle.left = 0;
    m_spriteRectangle.top = 0;

    setTextureRect(m_spriteRectangle);
}

void AnimatedSprite::addAnimation(
    const std::string& name,
    int startColumn,
    int startRow,
    int frameCount,
    float frameTime
) noexcept {
    if (startColumn < 0)
        startColumn = 0;
    else if (startColumn > m_columns - 1)
        startColumn = m_columns - 1;

    if (startRow < 0)
        startRow = 0;
    else if (startRow > m_rows - 1)
        startRow = m_rows - 1;

    int startFrameNumber = startRow * m_columns + startColumn;
    if (frameCount < 1)
        frameCount = 1;
    else if (startFrameNumber + frameCount >= m_columns * m_rows)
        frameCount = m_columns * m_rows - startFrameNumber;

    m_animations[name] = std::tuple<int, int, int, float>(
        startColumn, startRow, frameCount, frameTime);

    // If this is the first animation, play it by default
    if (m_currentAnimationName == "") {
        play(name);
    }
}

void AnimatedSprite::play(const std::string& name) noexcept {
    if (name == m_currentAnimationName) {
        return;
    }

    m_currentAnimationName = name;
    m_currentAnimation = m_animations[name];

    m_currentColumn = std::get<0>(m_currentAnimation);
    m_currentRow = std::get<1>(m_currentAnimation);

    m_currentFrameTime = 0.f;

    updateSpriteRectangle();
}

void AnimatedSprite::playAfter(const std::string& name) noexcept {
    m_nextAnimationName = name;
}

void AnimatedSprite::update(float deltaTime) noexcept {
    m_currentFrameTime += deltaTime;
    if (m_currentFrameTime >= std::get<3>(m_currentAnimation)) {
        m_currentFrameTime = 0.f;
        nextFrame();
    }
}

void AnimatedSprite::nextFrame() noexcept {
    int currentFrameNumber = m_currentRow * m_columns + m_currentColumn;
    int startFrameNumber = std::get<1>(m_currentAnimation) * m_columns
        + std::get<0>(m_currentAnimation);
    int endFrameNumber = startFrameNumber + std::get<2>(m_currentAnimation) - 1;

    if (currentFrameNumber >= endFrameNumber) {
        // If we're given an animation to play next, switch over
        if (m_nextAnimationName != "") {
            play(m_nextAnimationName);
            m_nextAnimationName = "";
            return;
        }

        m_currentColumn = std::get<0>(m_currentAnimation);
        m_currentRow = std::get<1>(m_currentAnimation);
    } else {
        if (m_currentColumn >= m_columns- 1) {
            m_currentColumn = 0;
            m_currentRow++;
        } else {
            m_currentColumn++;
        }
    }

    updateSpriteRectangle();
}

void AnimatedSprite::updateSpriteRectangle() noexcept {
    m_spriteRectangle.left = m_spriteRectangle.width * m_currentColumn;
    m_spriteRectangle.top = m_spriteRectangle.height * m_currentRow;
    setTextureRect(m_spriteRectangle);
}
