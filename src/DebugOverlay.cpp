#include "DebugOverlay.h"

#include <cassert>

DebugOverlay::DebugOverlay() {
}

DebugOverlay::~DebugOverlay() {
}

const sf::Sprite& DebugOverlay::get() const {
    return rect;
}

void DebugOverlay::set(const sf::Sprite& sprite) {
    inputSprite = &sprite;

    auto gb = sprite.getLocalBounds();

    if (!renderTexture.create(gb.width, gb.height))
        throw std::runtime_error("DebugOverlay::set - Failed to create texture ");

    rect.setTexture(renderTexture.getTexture());
}

void DebugOverlay::update() {
    assert(inputSprite);

    auto gb = inputSprite->getLocalBounds();

    sf::RectangleShape rectangle;
    rectangle.setScale(inputSprite->getScale());
    rectangle.setSize(sf::Vector2f(gb.width, gb.height));
    rectangle.setOrigin(gb.width / 2, gb.height / 2);
    rectangle.setPosition(inputSprite->getPosition());
    rectangle.setRotation(inputSprite->getRotation());

    int thickness = 3;
    int length = 15;
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    rectangle.setOutlineThickness(thickness);
    rectangle.setOutlineColor(sf::Color(100, 250, 50, 255));

    sf::RectangleShape vLine, hLine;
    vLine.setFillColor(sf::Color(100, 250, 50, 255));
    hLine.setFillColor(sf::Color(100, 250, 50, 255));
    vLine.setSize(sf::Vector2f(length, thickness));
    vLine.setOrigin(length / 2, thickness / 2);
    vLine.setPosition(inputSprite->getPosition());
    hLine.setSize(sf::Vector2f(thickness, length));
    hLine.setOrigin(thickness / 2, length / 2);
    hLine.setPosition(inputSprite->getPosition());
    hLine.setRotation(inputSprite->getRotation());
    vLine.setRotation(inputSprite->getRotation());

    renderTexture.clear();
    renderTexture.draw(*inputSprite);
    renderTexture.draw(rectangle);
    renderTexture.draw(vLine);
    renderTexture.draw(hLine);
    renderTexture.display();
}
