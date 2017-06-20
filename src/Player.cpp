#include "Player.h"
#include "TextureHolder.h"
#include "Utils.h"

#include <cassert>

Player::Player(std::string file):
    mSprite(nullptr) {

    TextureHolder& th = TextureHolder::getInstance();
    th.load(Textures::Audi, file);
    sf::Texture& t = th.get(Textures::Audi);
    t.setSmooth(true);
    mSprite = new sf::Sprite(t);
    mSprite->setScale(sf::Vector2f(0.5f, 0.5f));
    Utils::CenterOrigin(*mSprite);
}

Player::~Player() {
    if (mSprite)
        delete mSprite;
    mSprite = nullptr;
}

void Player::setPosition(float x, float y) {
    assert(mSprite);

    mSprite->setPosition(x, y);
}

void Player::move(sf::Vector2f delta) {
    assert(mSprite);

    mSprite->move(delta);
    mSprite->rotate(1);
}

const sf::Sprite& Player::get() {
    return *mSprite;
}
