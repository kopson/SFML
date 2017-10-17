#ifndef GAME_HPP
#define GAME_HPP

#include <DebugOverlay.hpp>
#include <Player.hpp>
#include <World.hpp>

#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


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
        void processInput();
        void update(sf::Time elapsedTime);
        void render();
        void updateStatistics(sf::Time elapsedTime);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        sf::RenderWindow mWindow;
        World mWorld;
        static const sf::Time TimePerFrame;
		Player mPlayer;
        bool mPaused;
        sf::Clock mClock;
        DebugOverlay mOverlay;

        sf::Font mFont;
        sf::Text mStatisticsText;
        sf::Time mStatisticsUpdateTime;
        std::size_t	mStatisticsNumFrames;
};

#endif // GAME_HPP
