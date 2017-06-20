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

class TextureHolder {
public:
    static TextureHolder& getInstance() {
        static TextureHolder instance;
        return instance;
    }
    TextureHolder() {}
    TextureHolder(TextureHolder const&) = delete;
    void operator=(TextureHolder const&) = delete;

    void load(Textures::ID id, const std::string& filename);
    sf::Texture& get(Textures::ID id);
    const sf::Texture& get(Textures::ID id) const;

private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif // TEXTUREHOLDER_H
