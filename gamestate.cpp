#include <iostream>

#include "gamestate.hpp"
#include "definitions.hpp"
#include "game.hpp"

namespace Sonar
{
    GameState::GameState( GameDataRef data) : _data(data) {}

    void GameState::init()
    {
        this->_data->assets.loadTexture("Background", GAME_BACKGROUND_FILEPATH);
        this->_data->assets.loadTexture("PauseButton", PAUSE_BUTTON_FILEPATH);

        this->_background.setTexture(this->_data->assets.getTexture("Background"));
        this->_pauseButton.setTexture(this->_data->assets.getTexture("PauseButton"));
        
        float pauseButtonPosX = this->_data->window.getSize().x - this->_pauseButton.getLocalBounds().width;
        float pauseButtonPosY = this->_pauseButton.getPosition().y;

        this->_pauseButton.setPosition(pauseButtonPosX, pauseButtonPosY);

        gameState = STATE_PLAYING;
        turn = STATE_PLACE;
    }

    void GameState::handleInput()
    {
        sf::Event e;

        while ( this->_data->window.pollEvent(e) )
        {
            if( sf::Event::Closed == e.type )
            {
                this->_data->window.close();
            }

            if ( this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window) )
            {
                std::cout << "Pausing game" << std::endl;
            }
        }
    }

    void GameState::update( float dt )
    {

    }

    void GameState::draw( float dt )
    {
        this->_data->window.clear();

        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_pauseButton);

        this->_data->window.display();
    }

}
