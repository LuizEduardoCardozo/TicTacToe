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
            void checkPlayerWon( int turn );
            void check3PiecesForMatch(sf::Vector2u p1, sf::Vector2u p2, sf::Vector2u p3, int player);

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

