#ifndef VEHICLE_H
#define VEHICLE_H

#include "Entity.h"
#include "ResourceHolder.h"

class Vehicle : public Entity {
public:
    enum Type {
        Audi,
        BMW
    };

    explicit Vehicle(Type type, const TextureHolder& textures);
    virtual ~Vehicle();

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Type mType;
    sf::Sprite mSprite;
};

#endif // VEHICLE_H
