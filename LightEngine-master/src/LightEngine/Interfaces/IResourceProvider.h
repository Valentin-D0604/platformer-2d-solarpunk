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
	virtual void LoadTexture(std::string _name) = 0;
	virtual void UnloadTexture(std::string _name) = 0;
	virtual sf::Texture* GetTexture(std::string _name) = 0;

	virtual void LoadFont(std::string _name) = 0;
	virtual void UnloadFont(std::string _name) = 0;
	virtual sf::Font* GetFont(std::string _name) = 0;
};