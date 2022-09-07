#include <iostream>

#include <SFML/Window/Event.hpp>

#include "definitions.hpp"
#include "pausestate.hpp"
#include "mainmenustate.hpp"

namespace Sonar
{
    PauseState::PauseState( GameDataRef data ) : _data( data ) {};

    void PauseState::init()
    {
        this->_data->assets.loadTexture("Background", PAUSE_BACKGROUND_FILEPATH);
        this->_data->assets.loadTexture("ResumeButton", RESUME_BUTTON_FILEPATH);
        this->_data->assets.loadTexture("HomeButton", HOME_BUTTON_FILEPATH);

        this->_background.setTexture(this->_data->assets.getTexture("Background"));
        this->_resumeButton.setTexture( this->_data->assets.getTexture("ResumeButton") );
        this->_homeButton.setTexture(this->_data->assets.getTexture("HomeButton"));

        float resumeButtonPosX = (this->_data->window.getSize().x / 2.0) - (this->_resumeButton.getLocalBounds().width / 2.0);
        float resumeButtonPosY = (this->_data->window.getSize().y / 3.0) - (this->_resumeButton.getLocalBounds().height / 2.0);

        this->_resumeButton.setPosition(resumeButtonPosY, resumeButtonPosY);

        float homeButtonPosX = resumeButtonPosX;
        float homeButtonPosY = (this->_data->window.getSize().y / (3.0 * 2.0)) - (this->_homeButton.getLocalBounds().height);

        this->_homeButton.setPosition(homeButtonPosX, homeButtonPosY);
    }

    void PauseState::handleInput()
    {
        sf::Event e;

        while(this->_data->window.pollEvent(e))
        {
            if(sf::Event::Closed == e.type)
            {
                this->_data->window.close();
            }

            if(this->_data->input.isSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->statemachine.removeState();
            }

            if(this->_data->input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->statemachine.removeState();
                this->_data->statemachine.addState(StateRef( new MainMenuState( this->_data ) ));
            }
        }
    }

    void PauseState::update( float dt )
    {

    }

    void PauseState::draw( float dt )
    {
        this->_data->window.clear();

        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_resumeButton);
        this->_data->window.draw(this->_homeButton); 

        this->_data->window.display();
    }

}
