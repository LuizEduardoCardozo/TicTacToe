#pragma once

#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "game.hpp"

namespace Sonar
{
    class GameState: public State
    {
        public:
            GameState( GameDataRef data );

            void init();

            void handleInput();
            void update( float dt );
            void draw( float dt );

        private:
            GameDataRef _data;

            sf::Sprite _background;

            sf::Sprite _pauseButton;

            int turn;
            int gameState;
    };
}

