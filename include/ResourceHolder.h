#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <cassert>
#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

namespace Textures {
    enum ID {
        Audi
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    static ResourceHolder& getInstance() {
        static ResourceHolder instance;
        return instance;
    }
    ResourceHolder() {}
    ResourceHolder(ResourceHolder const&) = delete;
    void operator=(ResourceHolder const&) = delete;

    void load(Identifier id, const std::string& filename);
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // TEXTUREHOLDER_H
