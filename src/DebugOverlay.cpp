#include "DebugOverlay.h"

#include <cassert>

DebugOverlay::DebugOverlay() {
}

DebugOverlay::~DebugOverlay() {
    //dtor
}

const sf::Sprite& DebugOverlay::get() {
    return rect;
}

void DebugOverlay::set(const sf::Sprite& sprite) {
    this->sprite = &sprite;

    auto gb = sprite.getLocalBounds();

    if (!renderTexture.create(gb.width, gb.height))
        throw std::runtime_error("DebugOverlay::set - Failed to create texture ");

    rect.setTexture(renderTexture.getTexture());
}

void DebugOverlay::update() {
    assert(sprite);

    auto gb = sprite->getLocalBounds();

    sf::RectangleShape rectangle;
    rectangle.setScale(sprite->getScale());
    rectangle.setSize(sf::Vector2f(gb.width, gb.height));
    rectangle.setOrigin(gb.width / 2, gb.height / 2);
    rectangle.setPosition(sprite->getPosition());
    rectangle.setRotation(sprite->getRotation());

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
    vLine.setPosition(sprite->getPosition());
    hLine.setSize(sf::Vector2f(thickness, length));
    hLine.setOrigin(thickness / 2, length / 2);
    hLine.setPosition(sprite->getPosition());
    hLine.setRotation(sprite->getRotation());
    vLine.setRotation(sprite->getRotation());

    renderTexture.clear();
    renderTexture.draw(*sprite);
    renderTexture.draw(rectangle);
    renderTexture.draw(vLine);
    renderTexture.draw(hLine);
    renderTexture.display();
}
