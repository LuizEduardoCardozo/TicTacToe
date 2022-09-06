#include <iostream>
#include <sstream>

#include "definitions.hpp"
#include "mainmenustate.hpp"
#include "game.hpp"

namespace Sonar 
{
    MainMenuState::MainMenuState( GameDataRef data ) : _data( data ) {}

    void MainMenuState::init()
    {
        this->_data->assets.loadTexture("Background", MAIN_MENU_BACKGROND_FILEPATH);
        this->_data->assets.loadTexture("PlayButton", MAIN_MENU_PLAY_BUTTON_FILEPATH);
        this->_data->assets.loadTexture("PlayButtonOuter", MAIN_MENU_PLAY_BUTTON_OUTER_FILEPATH);
        this->_data->assets.loadTexture("Title", MAIN_MENU_TITLE_FILEPATH);

        this->_background.setTexture( this->_data->assets.getTexture("Background") );
        this->_playButton.setTexture( this->_data->assets.getTexture("PlayButton") );
        this->_playButtonOuter.setTexture( this->_data->assets.getTexture("PlayButtonOuter") );
        this->_title.setTexture( this->_data->assets.getTexture("Title") );

        float playButtonPosX = (static_cast<float>(SCREEN_WIDTH)  / 2) - (this->_playButton.getGlobalBounds().width  / 2);
        float playButtonPosY = (static_cast<float>(SCREEN_HEIGHT)  / 2) - (this->_playButton.getGlobalBounds().height / 2);
      
        this->_playButton.setPosition(playButtonPosX, playButtonPosY);

        float playButtonOuterPosX = (static_cast<float>(SCREEN_WIDTH)  / 2) - (this->_playButtonOuter.getGlobalBounds().width / 2);
        float playButtonOuterPosY = (static_cast<float>(SCREEN_HEIGHT) / 2) - (this->_playButtonOuter.getGlobalBounds().height / 2);

        this->_playButtonOuter.setPosition(playButtonOuterPosX, playButtonOuterPosY);
        
        float titlePosX = (static_cast<float>(SCREEN_WIDTH) / 2) - (this->_title.getGlobalBounds().width / 2);
        float titlePosY = (static_cast<float>(SCREEN_HEIGHT) * 0.1);

        this->_title.setPosition(titlePosX, titlePosY);
    }

    void MainMenuState::handleInput()
    {
        sf::Event e;
        while( this->_data->window.pollEvent(e) )
        {
            if( sf::Event::Closed == e.type )
            {
                this->_data->window.close();
            }

            if( this->_data->input.isSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window) )
            {
                std::cout << "Going to the game screen!" << std::endl;
            }
        }
    }

    void MainMenuState::update( float dt )
    {
        
    }

    void MainMenuState::draw( float dt )
    {
        this->_data->window.clear();

        this->_data->window.draw( this->_background );
        this->_data->window.draw( this->_playButton );
        this->_data->window.draw( this->_playButtonOuter );
        this->_data->window.draw( this->_title );

        this->_data->window.display();
    }
}

