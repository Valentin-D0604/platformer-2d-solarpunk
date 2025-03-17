#include "ResourceManager.h"

const std::string TEMP_RES_PATH = "../../../res/";

#include "../Utils/OS.h"
#include "../Accessors/Resources.h"

ResourceManager::ResourceManager() {
	Resources::m_resources = this;
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
	//bool success = m_textures.find(_name) != m_textures.end();
	bool success = false;
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
sf::Font* ResourceManager::GetFont(std::string _name) {
	bool success = m_Fonts.find(_name) != m_Fonts.end();
	if (!success) {
		LoadFont(_name);
		success = m_Fonts.find(_name) != m_Fonts.end();
	}
	return &m_Fonts[_name];
}