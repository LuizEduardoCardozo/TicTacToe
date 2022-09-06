#include <iostream>
#include <sstream>

#include <SFML/Window/Event.hpp>

#include "game.hpp"
#include "mainmenustate.hpp"
#include "splashstate.hpp"
#include "definitions.hpp"

namespace Sonar
{
    SplashScreenState::SplashScreenState( GameDataRef data ) : _data( data )
    {

    }

    void SplashScreenState::init()
    {
        this->_data->assets.loadTexture("SplashStateBackground", SPLASH_SCREEN_BACKGROUND_FILEPATH);
        _background.setTexture( this->_data->assets.getTexture("SplashStateBackground") );
    }

    void SplashScreenState::handleInput()
    {
        sf::Event e;

        while( this->_data->window.pollEvent(e) )
        {
            if ( sf::Event::Closed == e.type )
            {
                this->_data->window.close();
            }
        }
    }

    void SplashScreenState::update(float dt)
    {
        if ( this->_clock.getElapsedTime().asSeconds() > SPLASH_SCREEN_SHOW_TIME)
        {
            this->_data->statemachine.addState( StateRef( new MainMenuState( this->_data ) ), true );
        }
    }

    void SplashScreenState::draw(float dt)
    {
        this->_data->window.clear( sf::Color::Blue );
        this->_data->window.draw( this->_background );
        this->_data->window.display();
    }

}

