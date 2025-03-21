#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

#include "../Interfaces/IResourceProvider.h"
#include "../Graphics/SpriteSheet.h"

class ResourceManager : IResourceProvider{
public:
	~ResourceManager();

	void LoadTexture(std::string _name);
	void UnloadTexture(std::string _name);
	sf::Texture* GetTexture(std::string _name);

	void LoadFont(std::string _name);
	void UnloadFont(std::string _name);
	sf::Font* GetFont(std::string _name);

	void LoadSoundBuffer(std::string _name);
	void UnloadSoundBuffer(std::string _name);
	sf::SoundBuffer* GetSoundBuffer(std::string _name);

	void LoadMusic(std::string _name);
	void UnloadMusic(std::string _name);
	sf::Music* GetMusic(std::string _name);

	void LoadSpriteSheet(std::string _name);
	SpriteSheet* GetSpriteSheet(std::string _name);


private:
	ResourceManager();

	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::Font> m_Fonts;
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;
	std::map<std::string, sf::Music> m_Musics;
	std::map<std::string, SpriteSheet*> m_SpriteSheets;

	void AddSoundBuffer(std::string _name, std::string _path);
	void AddMusic(std::string _name, std::string _path);
	void AddTexture(std::string _name, std::string _path);
	void AddFont(std::string _name, std::string _path);

	friend class Managers;
};