#include "Game.h"

#include <iostream>

Game::Game(int w, int h, std::string title):
    mWindow(sf::VideoMode(w, h), title),
    mPlayer("res/audi.png"),
    PlayerSpeed(30.0f),
    TimePerFrame(sf::seconds(1.f / 60.f)),
    mPaused(false) {

    init();
}

Game::~Game() {
    //dtor
}

void Game::init() {
    mPlayer.setPosition(100.f, 100.f);

    mWindow.setVerticalSyncEnabled(true);
    db.set(mPlayer.get());
}

void Game::run() {
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();
        if (!mPaused) {
            timeSinceLastUpdate += mClock.restart();
            while (timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
                update(TimePerFrame);
            }
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
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

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    switch(mMove) {
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

    mPlayer.move(movement * deltaTime.asSeconds());
    db.update();
}

void Game::render() {
    mWindow.clear();
    //mWindow.draw(mPlayer.get());
    mWindow.draw(db.get());
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
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
                if (mPaused)
                    resume();
                else
                    pause();
            break;
        default:
            mMove = Move::NONE;
            break;
    }
}

void Game::save() {

}
void Game::pause() {
    mPaused = true;
}

void Game::resume() {
    mClock.restart();
    mPaused = false;
}
