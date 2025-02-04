#include "pch.h"
#include "TextureLoader.h"

TextureLoader* TextureLoader::_instance = NULL;

TextureLoader::TextureLoader()
{
	assert(_instance == NULL);
	_instance = this;
}

sf::Texture& TextureLoader::loadTexture(std::string fullPath)
{
	std::map<std::string, sf::Texture>& texturesReference = _instance->_textures;

	// Try to found if a reference already exist of the texture
	std::map<std::string, sf::Texture>::iterator pair = texturesReference.find(fullPath);

	// Return the reference found or create a new one
	if (pair != texturesReference.end())
	{
		return pair->second;
	}

	sf::Texture& texture = texturesReference[fullPath];

	if (!texture.loadFromFile(fullPath))
	{
		std::cout << "RessourceLoader::loadTexture::" << fullPath << " not found." << std::endl;
		throw "RessourceLoader::loadTexture::" + fullPath + " not found.";
	}

	return texture;
}
