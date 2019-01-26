//
// Created by Christian Wilkerson on 2019-01-26.
//

#ifndef GGJ2019_NPC_H
#define GGJ2019_NPC_H


class NPC {
public:
    NPC();

    void initialize (Game&);
    void update (Game&, float deltaTime) noexcept;
    void react(std::shared_ptr<InteractiveObject> obj);

private:
    virtual void draw(sf::renderTarget& window, sf::renderState state);
    void pathing(float xDir, float yDir, float vel);

};


#endif //GGJ2019_NPC_H
