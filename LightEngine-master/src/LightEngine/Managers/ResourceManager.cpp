#include "ResourceManager.h"

const std::string TEMP_RES_PATH = "../../../res/";

#include "../Utils/OS.h"
#include "../Accessors/Resources.h"

ResourceManager::ResourceManager() {
	Resources::m_Resources = this;
}

ResourceManager::~ResourceManager()
{
	m_Textures.erase(m_Textures.begin(), m_Textures.end());
	m_Fonts.erase(m_Fonts.begin(), m_Fonts.end());
	m_SoundBuffers.erase(m_SoundBuffers.begin(), m_SoundBuffers.end());
}

void ResourceManager::loadTexture(std::string _name) {
	addTexture(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".png"));
}
void ResourceManager::unloadTexture(std::string _name) {
	m_Textures.erase(_name);
}
void ResourceManager::addTexture(std::string _name, std::string _path) {
	bool success = m_Textures[_name].loadFromFile(_path);
}
sf::Texture* ResourceManager::getTexture(std::string _name) {
	//bool success = m_textures.find(_name) != m_textures.end();
	bool success = false;
	if (!success) {
		loadTexture(_name);
		success = m_Textures.find(_name) != m_Textures.end();
	}
	return &m_Textures[_name];
}

void ResourceManager::loadFont(std::string _name) {
	addTexture(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".ttf"));
}

void ResourceManager::unloadFont(std::string _name) {
	m_Fonts.erase(_name);
}

void ResourceManager::addFont(std::string _name, std::string _path) {
	bool success = m_Fonts[_name].loadFromFile(_path);
}

void ResourceManager::addSoundBuffer(std::string _name, std::string _path)
{
	bool success = m_SoundBuffers[_name].loadFromFile(_path);
}

void ResourceManager::addMusic(std::string _name, std::string _path)
{
	bool success = m_Musics[_name].openFromFile(_path);
}

sf::Font* ResourceManager::getFont(std::string _name) {
	bool success = m_Fonts.find(_name) != m_Fonts.end();
	if (!success) {
		loadFont(_name);
		success = m_Fonts.find(_name) != m_Fonts.end();
	}
	return &m_Fonts[_name];
}

void ResourceManager::loadSoundBuffer(std::string _name)
{
	addSoundBuffer(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".mp3"));
}

void ResourceManager::unloadSoundBuffer(std::string _name)
{
	m_SoundBuffers.erase(_name);
}

sf::SoundBuffer* ResourceManager::getSoundBuffer(std::string _name)
{
	bool success = m_SoundBuffers.find(_name) != m_SoundBuffers.end();
	if (!success) {
		loadFont(_name);
		success = m_SoundBuffers.find(_name) != m_SoundBuffers.end();
	}
	return &m_SoundBuffers[_name];
}

void ResourceManager::loadMusic(std::string _name)
{
	addMusic(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".mp3"));
}

void ResourceManager::unloadMusic(std::string _name)
{
	m_Musics.erase(_name);
}

sf::Music* ResourceManager::getMusic(std::string _name)
{
	bool success = m_Musics.find(_name) != m_Musics.end();
	if (!success) {
		loadFont(_name);
		success = m_Musics.find(_name) != m_Musics.end();
	}
	return &m_Musics[_name];
}
