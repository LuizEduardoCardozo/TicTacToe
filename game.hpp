#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "statemachine.hpp"
#include "assetmanager.hpp"
#include "inputmanager.hpp"

namespace Sonar
{
    struct GameData
    {
        sf::RenderWindow window;
        StateMachine statemachine;
        AssetManager assets;
        InputManager input;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game
    {
        public:
            Game(int width, int heigh, std::string windowTitle);
            ~Game() {}

        private:
            const float dt = 1.0f / 60.0f;

            sf::Clock _clock;
            GameDataRef _data = std::make_shared<GameData>();

            void run();
    };
}


