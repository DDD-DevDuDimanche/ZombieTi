#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

class TextureLoader
{
public:
	TextureLoader();

	////////////////////////////////////////////////////////////
	/// Load a texture or create a new one
	/// \param fullPath : Complete path of the image (ex: img/ring.png)
	////////////////////////////////////////////////////////////
	static sf::Texture& loadTexture(std::string fullPath);

private:
	////////////////////////////////////////////////////////////
	/// Store texture reference when loaded
	////////////////////////////////////////////////////////////
	std::map<std::string, sf::Texture> _textures;

	static TextureLoader* _instance;
};

#endif TEXTURE_LOADER_H