#include "Utils.h"

void Utils::CenterOrigin(sf::Sprite& sprite) {
    sf::FloatRect spriteSize = sprite.getLocalBounds();
    sprite.setOrigin(spriteSize.width / 2, spriteSize.height / 2);
}
