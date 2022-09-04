#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Sonar
{
    class InputManager
    {
        public:
            InputManager() {}
            ~InputManager() {}

            bool isSpriteClicked( sf::Sprite obj, sf::Mouse::Button b, sf::RenderWindow &w );
            sf::Vector2i getMousePosition( sf::RenderWindow &w );
    };
}

