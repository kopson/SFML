#include "Entity.h"
#include "ResourceHolder.h"
#include "Utils.h"

#include <cassert>

Entity::Entity(std::string file):
    mSprite(nullptr) {

    TextureHolder& th = TextureHolder::getInstance();
    th.load(Textures::Audi, file);
    sf::Texture& t = th.get(Textures::Audi);
    t.setSmooth(true);
    mSprite = new sf::Sprite(t);
    mSprite->setScale(sf::Vector2f(0.5f, 0.5f));
    Utils::CenterOrigin(*mSprite);
}

Entity::~Entity() {
    if (mSprite)
        delete mSprite;
    mSprite = nullptr;
}

void Entity::setPosition(float x, float y) {
    assert(mSprite);

    mSprite->setPosition(x, y);
}

void Entity::move(sf::Vector2f delta) {
    assert(mSprite);

    mSprite->move(delta);
    mSprite->rotate(1);
}

const sf::Sprite& Entity::get() {
    return *mSprite;
}

void Entity::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
    return mVelocity;
}

void Entity::updateCurrent(sf::Time dt) {
    move(mVelocity * dt.asSeconds());
}
