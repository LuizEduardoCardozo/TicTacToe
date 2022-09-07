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
            void checkAndPlace();

            GameDataRef _data;

            sf::Sprite _background;
            sf::Sprite _grid;

            sf::Sprite _pauseButton;
            sf::Sprite _gridPlayers[3][3];

            int _gridStatus[3][3];

            int turn;
            int gameState;
    };
}

