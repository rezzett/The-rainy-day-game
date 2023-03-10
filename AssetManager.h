#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <memory>
#include <exception>

// TODO static method load all textures from array
class AssetManager
{
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
public:
	void addTexture(const std::string& path)
	{
		auto texture = std::make_shared<sf::Texture>();
		if (!texture->loadFromFile(path)) throw std::exception("Failed to load texture");
		textures[path] = std::move(texture);
	}

	const sf::Texture& getTexture(const std::string& textureName) const
	{
		return *(textures.at(textureName).get());
	}
};
