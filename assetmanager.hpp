#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <map>

namespace Sonar
{
    class AssetManager
    {
        public:
            AssetManager() {};
            ~AssetManager() {};

            void loadTexture( std::string name, std::string fileName );
            sf::Texture &getTexture( std::string name );

            void loadFont( std::string name, std::string fileName );
            sf::Font &getFont( std::string name );

        private:
            std::map<std::string, sf::Texture> _textures;
            std::map<std::string, sf::Font> _fonts;
    };
}


