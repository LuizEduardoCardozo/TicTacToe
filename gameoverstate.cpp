#include "definitions.hpp"

#include "gameoverstate.hpp"
#include "mainmenustate.hpp"
#include "gamestate.hpp"

namespace Sonar 
{
    GameOverState::GameOverState( GameDataRef data ) : _data( data ) {}

    void GameOverState::init()
    {
        this->_data->assets.loadTexture("RetryButton", RETRY_BUTTON_FILEPATH);
        this->_data->assets.loadTexture("HomeButton", HOME_BUTTON_FILEPATH);
    
        this->_retryButton.setTexture(this->_data->assets.getTexture("RetryButton"));
        this->_homeButton.setTexture(this->_data->assets.getTexture("HomeButton"));

        float retryButtonPosX = (this->_data->window.getSize().x / 2.0) - (this->_retryButton.getLocalBounds().width / 2.0);
        float retryButtonPosY = (this->_data->window.getSize().y / 3.0) - (this->_retryButton.getLocalBounds().height / 2.0);

        this->_retryButton.setPosition(retryButtonPosY, retryButtonPosY);

        float homeButtonPosX = retryButtonPosX;
        float homeButtonPosY = (this->_data->window.getSize().y / (3.0 * 2.0)) - (this->_homeButton.getLocalBounds().height);

        this->_homeButton.setPosition(homeButtonPosX, homeButtonPosY);
    }

    void GameOverState::handleInput()
    {
        sf::Event e;

        while ( this->_data->window.pollEvent(e))
        {
            if ( sf::Event::Closed == e.type )
            {
                this->_data->window.close();
            }

            if ( this->_data->input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window) )
            {
                this->_data->statemachine.addState(StateRef(new MainMenuState( this->_data )) );
            }

            if ( this->_data->input.isSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window) )
            {
                this->_data->statemachine.addState(StateRef(new GameState( this->_data )) );
            }
        }
    }

    void GameOverState::update(float dt)
    {
        
    }

    void GameOverState::draw(float dt)
    {
        this->_data->window.clear();

        this->_data->window.draw(this->_retryButton);
        this->_data->window.draw(this->_homeButton);

        this->_data->window.display();
    }
}
