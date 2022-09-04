#include "game.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace Sonar {
    Game::Game(int width, int height, std::string windowTitle)
    {
        _data->window.create(
            sf::VideoMode( width, height ), 
            windowTitle, 
            sf::Style::Close | sf::Style::Titlebar
        );
    }

    void Game::run()
    {
        float newTime, frameTime, interpolation;

        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (this->_data->window.isOpen())
        {
            this->_data->statemachine.processStateChanges();
            newTime = this->_clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if (frameTime > 0.25f)
            {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= dt)
            {
                this->_data->statemachine.getActiveState()->handleInput();
                this->_data->statemachine.getActiveState()->update(dt);

                accumulator -= dt;
            }
            
            interpolation = accumulator / dt;
            this->_data->statemachine.getActiveState()->draw(interpolation);

        }
    }
}

