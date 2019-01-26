#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Game.hpp"

class Bar {
    public:
        Bar(std::string barName) noexcept;
        Bar(std::string barName, int xPos, int yPos) noexcept;
        ~Bar();

        void addToGui(Game& game);
        void update(float incrementVal);
        void create(std::string barName);
        void setPosition(int xPos, int yPos);

    private:
        float m_percentage;
        tgui::ProgressBar::Ptr m_bar;

        std::string m_sanityText = "./data/themes/sanity.txt";
        std::string m_dangerText = "./data/themes/danger.txt";
};

#endif //BAR_H
