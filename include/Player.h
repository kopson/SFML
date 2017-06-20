#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <SFML/Graphics.hpp>

class Player {
    public:
        Player(std::string file);
        virtual ~Player();

        void setPosition(float x, float y);
        void move(sf::Vector2f delta);
        const sf::Sprite& get();

    private:
        sf::Sprite *mSprite;
};

#endif // PLAYER_H
