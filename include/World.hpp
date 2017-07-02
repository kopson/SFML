#ifndef WORLD_HPP
#define WORLD_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp>
#include <Vehicle.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

namespace sf {
	class RenderWindow;
}

class World : private sf::NonCopyable {
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();

private:
    void loadTextures();
    void buildScene();

    enum Layer {
        Background,
        Air,
        LayerCount
    };

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Vehicle* mPlayerCar;
};

#endif // WORLD_HPP
