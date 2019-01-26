#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Game.hpp"

class Bar {
    public:
        Bar(Game& game, int whichBar) noexcept;
        ~Bar();

        void update(float incrementVal);

    private:
        float m_percentage;
        tgui::ProgressBar::Ptr m_bar;

        std::string m_sanityText = "./data/themes/sanity.txt";
        std::string m_dangerText = "./data/themes/danger.txt";
};

#endif //BAR_H
