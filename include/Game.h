#ifndef GAME_H
#define GAME_H

#include <string>

#include <SFML/Graphics.hpp>

#include "DebugOverlay.h"
#include "Entity.h"

namespace Move {
    enum Moves { UP, DOWN, LEFT, RIGHT, NONE };
}

class Game {
    public:
        Game(int w, int h, std::string title);
        virtual ~Game();

        void run();
        void save();
        void pause();
        void resume();

    private:
        void init();
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        sf::RenderWindow mWindow;
        Entity mPlayer;
        const float PlayerSpeed;
        const sf::Time TimePerFrame;

        Move::Moves mMove;
        bool mPaused;
        sf::Clock mClock;
        DebugOverlay db;
};

#endif // GAME_H
