#include <utility>

#include "Bar.hpp"

Bar::Bar(std::string barName) noexcept {
    this->create(std::move(barName));
}

Bar::Bar(std::string barName, int xPos, int yPos) noexcept {
    this->create(std::move(barName));
    this->setPosition(xPos, yPos);
}

Bar::~Bar() {
    // Do nothing for now
}

void Bar::addToGui(Game& game) {
    auto& gui = game.getGui();

    gui.add(this->m_bar);
}

void Bar::update(float incrementVal) {
    this->m_percentage += incrementVal;

    int currVal = this->m_bar->getValue();
    int toAdd = (int) this->m_percentage;

    this->m_bar->setValue(static_cast<unsigned int>(currVal + toAdd));
}

void Bar::create(std::string barName) {
    tgui::Theme theme{this->m_sanityText};

    this->m_bar = tgui::ProgressBar::create();
    this->m_bar->setRenderer(theme.getRenderer("ProgressBar"));
    this->m_bar->setValue(0);
    this->m_bar->setMinimum(0);
    this->m_bar->setMaximum(100);
    this->m_bar->setText(barName);
    this->m_bar->setSize(200, 20);

    this->m_percentage = 0.f;\
}

void Bar::setPosition(int xPos, int yPos) {
    this->m_bar->setPosition(xPos, yPos);
}
