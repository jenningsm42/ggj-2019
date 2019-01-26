#include "Bar.hpp"

Bar::Bar(Game& game, int whichBar) noexcept {
    auto& gui = game.getGui();

    tgui::Theme theme{this->m_sanityText};

    this->m_bar = tgui::ProgressBar::create();
    this->m_bar->setRenderer(theme.getRenderer("ProgressBar"));
    this->m_bar->setPosition(10, 500);
    this->m_bar->setSize(200, 20);
    this->m_bar->setValue(0);
    this->m_bar->setMaximum(100);
    this->m_bar->setText("Sanity Bar");

    gui.add(this->m_bar);

    this->m_percentage = 0.f;
}

Bar::~Bar() {
    // Do nothing for now
}

void Bar::update(float incrementVal) {
    this->m_percentage += incrementVal;

    int currVal = this->m_bar->getValue();
    int toAdd = (int) this->m_percentage;
    this->m_bar->setValue(currVal + toAdd);
}
