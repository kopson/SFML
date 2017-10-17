#include <Game.hpp>
#include <StringHelpers.hpp>

#include <iostream>

#include <SFML/Window/Event.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(int w, int h, std::string title)
: mWindow(sf::VideoMode(w, h), title, sf::Style::Close)
, mWorld(mWindow)
, mPlayer()
, mPaused(false)
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
    init();
}

Game::~Game()
{
}

void Game::init()
{
	mWindow.setKeyRepeatEnabled(false);
    mFont.loadFromFile("res/fonts/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

    //mWindow.setVerticalSyncEnabled(true);
}

void Game::run()
{
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        if (!mPaused)
        {
            sf::Time elapsedTime = mClock.restart();
            timeSinceLastUpdate += elapsedTime;
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                processInput();
                update(TimePerFrame);
            }
            updateStatistics(elapsedTime);
        }
        else
        {
            processInput();
        }

        render();
    }
}

void Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

    sf::Event event;
    while (mWindow.pollEvent(event))
    {
		mPlayer.handleEvent(event, commands);

		if (event.type == sf::Event::Closed)
		{
			save();
            mWindow.close();
		}
		else if (event.type == sf::Event::LostFocus)
		{	
                pause();
		}
		else if (event.type == sf::Event::GainedFocus)
		{
                resume();
      	}
    }
	mPlayer.handleRealtimeInput(commands);
}

void Game::update(sf::Time elapsedTime)
{
    //mOverlay.update();
    mWorld.update(elapsedTime);
}

void Game::render()
{
    mWindow.clear();
	mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
        case sf::Keyboard::P:
            if (isPressed)
            {
                if (mPaused)
                    resume();
                else
                    pause();
            }
            break;
        default:
            break;
    }
}

void Game::save()
{
}

void Game::pause()
{
    mPaused = true;
}

void Game::resume()
{
    mClock.restart();
    mPaused = false;
}
