#ifndef GAME_HPP
#define GAME_HPP

#include <DebugOverlay.hpp>
#include <Entity.hpp>
#include <World.hpp>

#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Move
{
    enum Moves
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };
}

class Game : private sf::NonCopyable
{
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
        void updateStatistics(sf::Time elapsedTime);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        sf::RenderWindow mWindow;
        World mWorld;
        const float PlayerSpeed;
        static const sf::Time TimePerFrame;

        Move::Moves mMove;
        bool mPaused;
        sf::Clock mClock;
        DebugOverlay mOverlay;

        sf::Font mFont;
        sf::Text mStatisticsText;
        sf::Time mStatisticsUpdateTime;
        std::size_t	mStatisticsNumFrames;
};

#endif // GAME_HPP
