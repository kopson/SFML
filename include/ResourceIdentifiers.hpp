#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf {
	class Texture;
}

namespace Textures {
	enum ID {
	    Audi,
		Eagle,
		Raptor,
		Desert
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // RESOURCEIDENTIFIERS_HPP