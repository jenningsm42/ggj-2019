//
// Created by Christian Wilkerson on 2019-01-26.
//

#ifndef NPC_H
#define NPC_H


class NPC {
public:
    NPC();

    void initialize (Game&);
    void update (Game&, float deltaTime) noexcept;
    void react(std::shared_ptr<InteractiveObject> obj);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state);
    void pathing(float xDir, float yDir, float vel);

    AnimatedSprite m_sprite;
    std::string m_name;
};


#endif //GGJ2019_NPC_H
