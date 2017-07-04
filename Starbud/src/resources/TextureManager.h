#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../Resources.h"

class TextureManager
{
public:
	static void loadTexture(const std::string& name, const std::string& path); //Loads texture into map
	static sf::Texture& getRef(const std::string& key); //Returns texture with key
	static void clearTextures();

private:
	static std::map<std::string, sf::Texture> textures; //Texture Map

};