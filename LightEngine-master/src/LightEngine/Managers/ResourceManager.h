#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <map>

#include "../Interfaces/IResourceProvider.h"

class ResourceManager : IResourceProvider{
public:
	void loadTexture(std::string _name);
	void unloadTexture(std::string _name);
	sf::Texture* getTexture(std::string _name);

	void loadFont(std::string _name);
	void unloadFont(std::string _name);
	sf::Font* getFont(std::string _name);

private:
	ResourceManager();

	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::Font> m_Fonts;

	void addTexture(std::string _name, std::string _path);
	void addFont(std::string _name, std::string _path);

	friend class Managers;
};