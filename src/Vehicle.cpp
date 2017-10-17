#include <Vehicle.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(Vehicle::Type type)
{
    switch (type)
    {
        case Vehicle::Audi:
            return Textures::Audi;
        case Vehicle::Eagle:
			return Textures::Eagle;
		case Vehicle::Raptor:
			return Textures::Raptor;
        default:
            assert(false);
    }
}

Vehicle::Vehicle(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Vehicle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Vehicle::getCategory() const
{
	switch (mType)
	{
		case Eagle:
			return Category::PlayerAircraft;

		default:
			return Category::EnemyAircraft;
	}
}
