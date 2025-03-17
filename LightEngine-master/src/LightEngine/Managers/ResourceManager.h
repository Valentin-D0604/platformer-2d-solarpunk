#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <map>

#include "../Interfaces/IResourceProvider.h"

class ResourceManager : IResourceProvider{
public:
	void LoadTexture(std::string _name);
	void UnloadTexture(std::string _name);
	sf::Texture* GetTexture(std::string _name);

	void LoadFont(std::string _name);
	void UnloadFont(std::string _name);
	sf::Font* GetFont(std::string _name);

private:
	ResourceManager();

	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::Font> m_Fonts;

	void AddTexture(std::string _name, std::string _path);
	void AddFont(std::string _name, std::string _path);

	friend class Managers;
};