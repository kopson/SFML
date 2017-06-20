#include "Vehicle.h"

Textures::ID toTextureID(Vehicle::Type type) {
    switch (type) {
        case Vehicle::Audi:
            return Textures::Audi;
        default:
            assert(false);
    }
}

Vehicle::Vehicle(Type type, const TextureHolder& textures):
    mType(type),
    mSprite(textures.get(toTextureID(type))) {
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Vehicle::~Vehicle() {
}

void Vehicle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}
