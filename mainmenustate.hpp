#pragma once

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "state.hpp"

namespace Sonar
{
    class MainMenuState : public State
    {
        public:
            MainMenuState( GameDataRef data );
            ~MainMenuState();

            void init();
            void handleInput();
            void update( float dt );
            void draw( float dt );
        
        private:
            GameDataRef _data;

            sf::Sprite _background;
            sf::Sprite _playButton;
            sf::Sprite _playButtonOuter;
            sf::Sprite _title;
    };
}

