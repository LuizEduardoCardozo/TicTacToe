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
            else if( this->_data->input.isSpriteClicked(this->_grid, sf::Mouse::Left, this->_data->window) )
            {
                checkAndPlace();
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

    void GameState::checkAndPlace()
    {
        sf::Vector2i touchedPoint = this->_data->input.getMousePosition(this->_data->window);
        sf::FloatRect gridSize = this->_grid.getGlobalBounds();

        sf::Vector2f gapOutsideOfGrid = sf::Vector2f(
            (SCREEN_WIDTH - gridSize.width ) / 2,
            (SCREEN_HEIGHT - gridSize.height) / 2
        );

        sf::Vector2f gridLocalTouchedPoint = sf::Vector2f(
            touchedPoint.x - gapOutsideOfGrid.x,
            touchedPoint.y - gapOutsideOfGrid.y
        );

        sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);
        
        int col, row;

        if (gridLocalTouchedPoint.x < gridSectionSize.x)
        {
            col = 0;
        } 
        else if (gridLocalTouchedPoint.x < 2 * gridSectionSize.x)
        {
            col = 1;
        }
        else if (gridLocalTouchedPoint.x < 3 * gridSectionSize.x)
        {
            col = 2;
        }

        if (gridLocalTouchedPoint.y < gridSectionSize.y)
        {
            row = 0;
        }
        else if (gridLocalTouchedPoint.y < 2 * gridSectionSize.y)
        {
            row = 1;
        }
        else if (gridLocalTouchedPoint.y < 3 * gridSectionSize.y)
        {
            row = 2;
        }

        if(this->_gridStatus[col][row] == EMPTY_SPACE)
        {
            std::cout << "you have clicked on the column " << col << " and the row " << row << " | turn: " << turn << std::endl;
            _gridStatus[col][row] = turn;

            if(turn == X_PLAYER)
            {
                _gridPlayers[col][row].setTexture( this->_data->assets.getTexture("XPlayer") );
                turn = O_PLAYER;
            }
            else if(turn == O_PLAYER)
            {
                _gridPlayers[col][row].setTexture( this->_data->assets.getTexture("OPlayer") );
                turn = X_PLAYER;
            }
        }

        this->_gridPlayers[col][row].setColor( sf::Color(255, 255, 255, 255) );

    }

}
