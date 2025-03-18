#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
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

	void loadSoundBuffer(std::string _name);
	void unloadSoundBuffer(std::string _name);
	sf::SoundBuffer* getSoundBuffer(std::string _name);

	void loadMusic(std::string _name);
	void unloadMusic(std::string _name);
	sf::Music* getMusic(std::string _name);

private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::Font> m_Fonts;
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;
	std::map<std::string, sf::Music> m_Musics;

	void addSoundBuffer(std::string _name, std::string _path);
	void addMusic(std::string _name, std::string _path);
	void AddTexture(std::string _name, std::string _path);
	void AddFont(std::string _name, std::string _path);

	friend class Managers;
};