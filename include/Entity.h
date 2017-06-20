#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <SFML/Graphics.hpp>

class Entity {
    public:
        Entity() {};
        Entity(std::string file);
        virtual ~Entity();

        void setPosition(float x, float y);
        void move(sf::Vector2f delta);
        const sf::Sprite& get();

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        sf::Vector2f getVelocity() const;

        virtual void updateCurrent(sf::Time dt);

    private:
        sf::Sprite *mSprite;
        sf::Vector2f mVelocity;
};

#endif // ENTITY_H
