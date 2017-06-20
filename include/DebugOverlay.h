#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

#include <SFML/Graphics.hpp>

class DebugOverlay
{
    public:
        DebugOverlay();
        virtual ~DebugOverlay();
        const sf::Sprite& get();
        void set(const sf::Sprite& sprite);
        void update();

    private:
        sf::RenderTexture renderTexture;
        const sf::Sprite* sprite;
        sf::Sprite rect;
};

#endif // DEBUGOVERLAY_H
