//
// Created by Christian Wilkerson on 2019-01-26.
//

#include <cmath>
#include <set>
#include "NPC.hpp"

NPC::NPC(std::string inputName)
        : m_dir(4),
          m_velocity(2.f),
          m_stopFlag(0.f),
          m_stopTimer(0.f),
          m_reactTimer(0.f),
          m_name(inputName),
          m_pastType(ObjectType::None)
{
    // Do nothing
}

void NPC::initialize (Game &game, float tileLength) noexcept {
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

    this->m_tileLength = tileLength;

    this->initGraph();
}

void NPC::update(Game& game, float deltaTime) noexcept {
    auto currPos = m_npcSprite.getPosition();
    // auto nextPos = sf::Vector2f(currPos.x * this->m_velocity, currPos.y * this->m_velocity);

    this->m_reactTimer += deltaTime;

    if (this->m_reactTimer >= 1.f and this->m_pastType != ObjectType::None) {
        this->react(this->m_pastType, this->m_pastPos, deltaTime);
    }

    this->m_stopFlag += deltaTime;

    if (this->m_stopFlag >= 5.f) {
        this->m_stopTimer += deltaTime;

        if (this->m_stopTimer >= 1.f) {
            this->m_stopFlag = 0.f;
            this->m_stopTimer = 0.f;
        }

        this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Stop, 0);
        return;
    }

    // Check map
    // If nextPos is object, turn
    // Else, go straight
    this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Straight, 7);

    auto& input = game.getInputHandler();
    if (input.getKeyTapped(sf::Keyboard::G)) {
        m_showGraph = !m_showGraph;
    }
}

void NPC::react(ObjectType objType, sf::Vector2f objPos, float deltaTime) {
    this->m_pastType = objType;
    this->m_pastPos = objPos;
    auto currPos = m_npcSprite.getPosition();

    auto modX = std::fabs(currPos.x - objPos.x);
    auto modY = std::fabs(currPos.y - objPos.y);
    auto eDistance = sqrtf(pow(modX, 2.0) + pow(modY, 2.0));

    // Doesn't effect NPC if not within effective range
    if (eDistance > 2.f * this->m_tileLength) {
        return;
    }

    // Check if player is spamming react
    if (this->m_reactTimer < 1.f) {
        this->m_reactTimer = 0.f;
        this->pathing(currPos.x, currPos.y, deltaTime, MovementType::SlowBack, 0.1f);
        return;
    }

    float speed = 0.f;
    float modifier = sqrtf(eDistance);

    switch (objType) {
        case ObjectType::Door:
            speed = modifier * this->m_reactSpeed[ObjectType::Door];
            this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Scared, speed);
            break;
        case ObjectType::Stove:
            speed = modifier * this->m_reactSpeed[ObjectType::Stove];
            this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Scared, speed);
            break;
        case ObjectType::Sink:
            speed = modifier * this->m_reactSpeed[ObjectType::Sink];
            this->pathing(currPos.x, currPos.y, deltaTime, MovementType::Scared, speed);
            break;
        default:
            // Should never get to here
            break;
    }

    this->m_reactTimer = 0.f;
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_npcSprite, states);

    if (m_showGraph) {
        sf::Sprite graphSprite;
        graphSprite.setTexture(m_graphTexture);
        target.draw(graphSprite, states);
    }
}

void NPC::pathing(float xPos, float yPos, float deltaTime, MovementType react, float velocity) {
    int randX = rand()% -1 +1;
    int randY = rand()% -1 +1;

    if (xPos*randX == xPos) {
        randX = rand()% -1 +1;
    }

    if (yPos*randY == yPos) {
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
            switch (this->m_dir) {
                // 1 is up, 2 is right, 3 is down, 4 is left
                case 1:
                    m_npcSprite.move(0 , -this->m_velocity*deltaTime*velocity);
                    break;
                case 2:
                    m_npcSprite.move(this->m_velocity*deltaTime*velocity, 0);
                    break;
                case 3:
                    m_npcSprite.move(0 , this->m_velocity*deltaTime*velocity);
                    break;
                case 4:
                    m_npcSprite.move(-this->m_velocity*deltaTime*velocity, 0);
                    break;
                default:
                    break;
            }
            m_npcSprite.play("run");
            m_npcSprite.setScale(this->m_velocity,this->m_velocity);
            break;
        case MovementType::Stop:
            m_npcSprite.move(0,0);
            m_npcSprite.play("idle");
            m_npcSprite.setScale(this->m_velocity, this->m_velocity);
            break;
        default:
            break;
    }

    m_npcSprite.update(deltaTime);
}

void NPC::initReactions() {
    this->m_reactSpeed[ObjectType::Door] = 1.3f;
}

void NPC::initGraph() {
    m_positions.push_back(std::pair<float, float>(215.f, 340.f));
    m_positions.push_back(std::pair<float, float>(215.f, 405.f));
    m_positions.push_back(std::pair<float, float>(88.f, 405.f));

    m_positions.push_back(std::pair<float, float>(215.f, 475.f));
    m_positions.push_back(std::pair<float, float>(330.f, 475.f));
    m_positions.push_back(std::pair<float, float>(340.f, 340.f));

    m_positions.push_back(std::pair<float, float>(350.f, 180.f));
    m_positions.push_back(std::pair<float, float>(415.f, 180.f));
    m_positions.push_back(std::pair<float, float>(470.f, 180.f));

    m_positions.push_back(std::pair<float, float>(650.f, 210.f));
    m_positions.push_back(std::pair<float, float>(540.f, 340.f));
    m_positions.push_back(std::pair<float, float>(540.f, 475.f));

    m_positions.push_back(std::pair<float, float>(540.f, 700.f));
    m_positions.push_back(std::pair<float, float>(670.f, 500.f));
    m_positions.push_back(std::pair<float, float>(790.f, 700.f));

    m_positions.push_back(std::pair<float, float>(790.f, 475.f));
    m_positions.push_back(std::pair<float, float>(790.f, 340.f));
    m_positions.push_back(std::pair<float, float>(790.f, 210.f));

    m_positions.push_back(std::pair<float, float>(790.f, 150.f));
    m_positions.push_back(std::pair<float, float>(920.f, 150.f));
    m_positions.push_back(std::pair<float, float>(980.f, 150.f));

    m_positions.push_back(std::pair<float, float>(920.f, 210.f));
    m_positions.push_back(std::pair<float, float>(920.f, 340.f));

    // Render graph
    sf::RenderTexture renderTexture;
    renderTexture.create(1000, 1000);
    renderTexture.clear(sf::Color::Transparent);

    const float circleRadius = 10.f;

    for (int i = 0; i < 23; i++) {
        for (int j = 0; j < 23; j++) {
            if (m_adjMatrix[i][j] == 1) {
                auto v1 = m_positions[i];
                auto v2 = m_positions[j];
                float dx = v2.first - v1.first;
                float dy = v2.second - v1.second;

                float angle = std::atan2(dy, dx);
                float length = sqrtf(dx * dx + dy * dy);

                sf::RectangleShape lineShape(sf::Vector2f(length, 2.f));
                lineShape.setOrigin(1.f, 1.f);
                lineShape.rotate(angle * 180.f / 3.14159f);
                lineShape.setPosition(v1.first + circleRadius, v1.second + circleRadius);
                lineShape.setFillColor(sf::Color::Red);

                renderTexture.draw(lineShape);
            }
        }
    }

    for (auto &pos : m_positions) {
         sf::CircleShape currShape(circleRadius);
         currShape.setPosition(pos.first, pos.second);
         currShape.setFillColor(sf::Color::Red);
         renderTexture.draw(currShape);
    }

    renderTexture.display();
    m_graphTexture = renderTexture.getTexture();
}

std::vector<int> NPC::getPathNodes(int sourceIndex, int endIndex) noexcept {
    std::queue<std::vector<int>> toVisit;
    std::set<int> visited;

    std::vector<int> path;
    path.push_back(sourceIndex);
    toVisit.push(path);

    while (!toVisit.empty()) {
        auto current = toVisit.front();
        toVisit.pop();

        if (current.back() == endIndex) {
            return current;
        }

        for (auto& other : m_adjMatrix[current.back()]) {
            auto it = visited.find(other);
            if (it != visited.end()) {
                std::vector<int> newPath = current;
                newPath.push_back(other);
                toVisit.push(newPath);
            }
        }
    }

    return std::vector<int>();
}
