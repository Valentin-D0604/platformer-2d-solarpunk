#pragma once

#include <string>

class IResourceProvider;

namespace sf {
	class Texture;
	class Font;
}

class Resources {
public:
	static void loadTexture(std::string _name);
	static void unloadTexture(std::string _name);
	static sf::Texture* getTexture(std::string _name);

	static void loadFont(std::string _name);
	static void unloadFont(std::string _name);
	static sf::Font* getFont(std::string _name);

private:
	static IResourceProvider* m_resources;

	friend class ResourceManager;
};