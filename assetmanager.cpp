#include "assetmanager.hpp"

namespace Sonar
{
    void AssetManager::loadTexture(std::string name, std::string fileName)
    {
        sf::Texture t;
        if (t.loadFromFile(fileName))
        {
            this->_textures[name] = t;
        }
    };

    sf::Texture &AssetManager::getTexture(std::string name)
    {
        return this->_textures.at(name);
    }


    void AssetManager::loadFont(std::string name, std::string fileName)
    {
        sf::Font f;
        if(f.loadFromFile(fileName))
        {
            this->_fonts[name] = f;
        }
    }

    sf::Font &AssetManager::getFont(std::string name)
    {
        return this->_fonts.at(name);
    }
}

