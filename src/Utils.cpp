#include "Utils.h"

void Utils::CenterOrigin(sf::Sprite& sprite) {
    sf::FloatRect spriteSize = sprite.getLocalBounds();
    float height = spriteSize.height;
    float width = spriteSize.width;
    sprite.setOrigin(width / 2, height / 2);
}
