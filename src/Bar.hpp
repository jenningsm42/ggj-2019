#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Game.hpp"

class Bar {
    public:
        Bar(Game &game, std::string barName) noexcept;
        Bar(Game &game, std::string barName, int xPos, int yPos) noexcept;
        ~Bar();

        void update(float incrementVal);
        void setPosition(int xPos, int yPos);

    private:
        float m_percentage;
        tgui::ProgressBar::Ptr m_bar;

        std::string m_sanityText = "./data/themes/sanity.txt";
        std::string m_dangerText = "./data/themes/danger.txt";
};

#endif //BAR_H
