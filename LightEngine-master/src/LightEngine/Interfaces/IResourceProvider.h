#pragma once

#pragma region External Dependencies

#include <string>

#pragma endregion

namespace sf {
	class Texture;
	class Font;
}

class IResourceProvider {
public:
	virtual void loadTexture(std::string _name) = 0;
	virtual void unloadTexture(std::string _name) = 0;
	virtual sf::Texture* getTexture(std::string _name) = 0;

	virtual void loadFont(std::string _name) = 0;
	virtual void unloadFont(std::string _name) = 0;
	virtual sf::Font* getFont(std::string _name) = 0;
};