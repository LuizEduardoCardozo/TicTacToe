#include "inputmanager.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Sonar
{
    bool InputManager::isSpriteClicked(sf::Sprite obj, sf::Mouse::Button b, sf::RenderWindow &w)
    {
        if(sf::Mouse::isButtonPressed(b))
        {
            float objPosX = obj.getPosition().x;
            float objPosY = obj.getPosition().y;
            
            float objHeight = obj.getGlobalBounds().height;
            float objWidth = obj.getGlobalBounds().width;

            sf::IntRect tmpRect(objPosX, objPosY, objWidth, objHeight);

            return tmpRect.contains(sf::Mouse::getPosition(w));
        }

        return false;
    }

    sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &w)
    {
        return sf::Mouse::getPosition(w);
    }
}

