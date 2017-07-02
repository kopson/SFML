#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Vehicle : public Entity
{
    public:
        enum Type
        {
            Audi,
            BMW,
            Raptor,
            Eagle
        };

        explicit Vehicle(Type type, const TextureHolder& textures);

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        Type mType;
        sf::Sprite mSprite;
};

#endif // VEHICLE_HPP
