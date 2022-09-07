#include "state.hpp"
#include "game.hpp"

namespace Sonar 
{
    class GameOverState : public State
    {
        public:
            GameOverState( GameDataRef data );

            void init();
     
            void handleInput();
    
            void update(float dt);
            void draw(float dt);
    
        private:
            GameDataRef _data;

            sf::Sprite _background;

            sf::Sprite _retryButton;
            sf::Sprite _homeButton;
    
    };
}
