#pragma once

#include <string>

class IResourceProvider;

namespace sf {
	class Texture;
	class Font;
}

class Resources {
public:
	static void LoadTexture(std::string _name);
	static void UnloadTexture(std::string _name);
	static sf::Texture* GetTexture(std::string _name);

	static void LoadFont(std::string _name);
	static void UnloadFont(std::string _name);
	static sf::Font* GetFont(std::string _name);

private:
	static IResourceProvider* m_resources;

	friend class ResourceManager;
};