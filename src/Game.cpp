#include <Game.hpp>
#include <StringHelpers.hpp>

#include <iostream>

#include <SFML/Window/Event.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(int w, int h, std::string title)
: mWindow(sf::VideoMode(w, h), title, sf::Style::Close)
, mWorld(mWindow)
, PlayerSpeed(30.0f)
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
    mFont.loadFromFile("res/fonts/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

    //mWindow.setVerticalSyncEnabled(true);
    //db.set(mPlayer.get());
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
                processEvents();
                update(TimePerFrame);
            }
            updateStatistics(elapsedTime);
        }
        else
        {
            processEvents();
        }

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                save();
                mWindow.close();
            break;

            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
            break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
            break;

            case sf::Event::Resized:
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            break;

            case sf::Event::LostFocus:
                pause();
            break;

            case sf::Event::GainedFocus:
                resume();
            break;

            case sf::Event::TextEntered:
                 if (event.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            break;

            default:
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    switch(mMove)
    {
        case Move::UP:
            movement.y -= PlayerSpeed;
            break;
        case Move::DOWN:
            movement.y += PlayerSpeed;
            break;
        case Move::LEFT:
            movement.x -= PlayerSpeed;
            break;
        case Move::RIGHT:
            movement.x += PlayerSpeed;
            break;
        default:
            break;
    }

    //mOverlay.update();
    mWorld.update(deltaTime);
}

void Game::render()
{
    mWindow.clear();
	mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
    //mWindow.draw(mOverlay.get());
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
        case sf::Keyboard::W:
            mMove = isPressed ? Move::UP : Move::NONE;
            break;
        case sf::Keyboard::S:
            mMove = isPressed ? Move::DOWN : Move::NONE;
            break;
        case sf::Keyboard::A:
            mMove = isPressed ? Move::LEFT : Move::NONE;
            break;
        case sf::Keyboard::D:
            mMove = isPressed ? Move::RIGHT : Move::NONE;
            break;
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
            mMove = Move::NONE;
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
