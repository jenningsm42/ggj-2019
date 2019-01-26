#include "Bar.hpp"

Bar::Bar(Game &game, std::string barName) noexcept {
    auto& gui = game.getGui();

    tgui::Theme theme{this->m_sanityText};

    this->m_bar = tgui::ProgressBar::create();
    this->m_bar->setRenderer(theme.getRenderer("ProgressBar"));
    this->m_bar->setValue(0);
    this->m_bar->setMinimum(0);
    this->m_bar->setMaximum(100);
    this->m_bar->setText(barName);

    this->m_bar->setSize(200, 20);

    gui.add(this->m_bar);

    this->m_percentage = 0.f;
}

Bar::Bar(Game &game, std::string barName, int xPos, int yPos) noexcept {
    auto& gui = game.getGui();

    tgui::Theme theme{this->m_sanityText};

    this->m_bar = tgui::ProgressBar::create();
    this->m_bar->setRenderer(theme.getRenderer("ProgressBar"));
    this->m_bar->setValue(0);
    this->m_bar->setMinimum(0);
    this->m_bar->setMaximum(100);
    this->m_bar->setText(barName);

    this->m_bar->setSize(200, 20);
    this->setPosition(xPos, yPos);

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

    this->m_bar->setValue(static_cast<unsigned int>(currVal + toAdd));
}

void Bar::setPosition(int xPos, int yPos) {
    this->m_bar->setPosition(xPos, yPos);
}
