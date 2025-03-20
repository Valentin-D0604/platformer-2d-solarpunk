#include "ResourceManager.h"

const std::string TEMP_RES_PATH = "../../../res/";

#include "../Utils/OS.h"
#include "../Accessors/Resources.h"
#include "../Entity/Entity.h"

ResourceManager::ResourceManager() {
	Resources::m_resources = this;
}


ResourceManager::~ResourceManager()
{
	m_Textures.erase(m_Textures.begin(), m_Textures.end());
	m_Fonts.erase(m_Fonts.begin(), m_Fonts.end());
	m_SoundBuffers.erase(m_SoundBuffers.begin(), m_SoundBuffers.end());
}

void ResourceManager::LoadTexture(std::string _name) {
	AddTexture(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".png"));
}
void ResourceManager::UnloadTexture(std::string _name) {
	m_Textures.erase(_name);
}
void ResourceManager::AddTexture(std::string _name, std::string _path) {
	bool success = m_Textures[_name].loadFromFile(_path);
}
sf::Texture* ResourceManager::GetTexture(std::string _name) {
	bool success = m_Textures.find(_name) != m_Textures.end();
	//bool success = false;
	if (!success) {
		LoadTexture(_name);
		success = m_Textures.find(_name) != m_Textures.end();
	}
	return &m_Textures[_name];
}

void ResourceManager::LoadFont(std::string _name) {
	AddTexture(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".ttf"));
}

void ResourceManager::UnloadFont(std::string _name) {
	m_Fonts.erase(_name);
}

void ResourceManager::AddFont(std::string _name, std::string _path) {
	bool success = m_Fonts[_name].loadFromFile(_path);
}

void ResourceManager::AddSoundBuffer(std::string _name, std::string _path)
{
	bool success = m_SoundBuffers[_name].loadFromFile(_path);
}

void ResourceManager::AddMusic(std::string _name, std::string _path)
{
	bool success = m_Musics[_name].openFromFile(_path);
}

sf::Font* ResourceManager::GetFont(std::string _name) {
	bool success = m_Fonts.find(_name) != m_Fonts.end();
	if (!success) {
		LoadFont(_name);
		success = m_Fonts.find(_name) != m_Fonts.end();
	}
	return &m_Fonts[_name];
}

void ResourceManager::LoadSoundBuffer(std::string _name)
{
	AddSoundBuffer(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".mp3"));
}

void ResourceManager::UnloadSoundBuffer(std::string _name)
{
	m_SoundBuffers.erase(_name);
}

sf::SoundBuffer* ResourceManager::GetSoundBuffer(std::string _name)
{
	bool success = m_SoundBuffers.find(_name) != m_SoundBuffers.end();
	if (!success) {
		LoadFont(_name);
		success = m_SoundBuffers.find(_name) != m_SoundBuffers.end();
	}
	return &m_SoundBuffers[_name];
}

void ResourceManager::LoadMusic(std::string _name)
{
	AddMusic(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".mp3"));
}

void ResourceManager::UnloadMusic(std::string _name)
{
	m_Musics.erase(_name);
}

sf::Music* ResourceManager::GetMusic(std::string _name)
{
	bool success = m_Musics.find(_name) != m_Musics.end();
	if (!success) {
		LoadFont(_name);
		success = m_Musics.find(_name) != m_Musics.end();
	}
	return &m_Musics[_name];
}

void ResourceManager::LoadSpriteSheet(std::string _name)
{
	m_SpriteSheets[_name] = new SpriteSheet(_name);
}

SpriteSheet* ResourceManager::GetSpriteSheet(std::string _name)
{
	bool success = m_SpriteSheets.find(_name) != m_SpriteSheets.end();
	if (!success) {
		LoadSpriteSheet(_name);
	}
	return m_SpriteSheets[_name];
}
