#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <alloca.h>
#include <iostream>

#include "gamestate.hpp"
#include "definitions.hpp"
#include "game.hpp"
#include "pausestate.hpp"

namespace Sonar
{
    GameState::GameState( GameDataRef data) : _data(data) {}

    void GameState::init()
    {
        this->_data->assets.loadTexture("Background", GAME_BACKGROUND_FILEPATH);
        this->_data->assets.loadTexture("PauseButton", PAUSE_BUTTON_FILEPATH);
        this->_data->assets.loadTexture("Grid", GRID_FILEPATH);
        this->_data->assets.loadTexture("XPlayer", X_PLAYER_FILEPATH);
        this->_data->assets.loadTexture("OPlayer", O_PLAYER_FILEPATH);

        this->_background.setTexture(this->_data->assets.getTexture("Background"));
        this->_pauseButton.setTexture(this->_data->assets.getTexture("PauseButton"));
        this->_grid.setTexture(this->_data->assets.getTexture("Grid"));

        float pauseButtonPosX = this->_data->window.getSize().x - this->_pauseButton.getLocalBounds().width;
        float pauseButtonPosY = this->_pauseButton.getPosition().y;

        this->_pauseButton.setPosition(pauseButtonPosX, pauseButtonPosY);

        float gridPosX = (SCREEN_WIDTH  / 2.0) - (this->_grid.getLocalBounds().width  / 2.0);
        float gridPosY = (SCREEN_HEIGHT / 2.0) - (this->_grid.getLocalBounds().height / 2.0);

        this->_grid.setPosition(gridPosX, gridPosY);

        sf::Texture playerTexture = this->_data->assets.getTexture("XPlayer");
        sf::Vector2u playerSize = playerTexture.getSize();

        for ( size_t l = 0; l < 3; l++ )
        {
            for ( size_t c = 0; c < 3; c++ )
            {
                this->_gridStatus[l][c] = EMPTY_SPACE;
                this->_gridPlayers[l][c].setTexture(playerTexture);

                sf::Vector2f gridPos = this->_grid.getPosition();

                float playerPosX = gridPos.x + (playerSize.x * l) - 3;
                float playerPosY = gridPos.y + (playerSize.y * c) - 3;

                this->_gridPlayers[l][c].setPosition(
                    playerPosX,
                    playerPosY
                );

                this->_gridPlayers[l][c].setColor(
                    sf::Color(255, 255, 255, 0)
                );
            }
        }

        gameState = STATE_PLAYING;
        turn = X_PLAYER;
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
                this->_data->statemachine.addState( StateRef( new PauseState( this->_data ) ), false );
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
        this->_data->window.draw(this->_grid);
        this->_data->window.draw(this->_pauseButton);

        for ( size_t l = 0; l < 3; l++ )
        {
            for ( size_t c = 0; c < 3; c++ )
            {
                this->_data->window.draw(this->_gridPlayers[l][c]);
            }
        }

        this->_data->window.display();
    }

}
