#include "ResourceManager.h"

const std::string TEMP_RES_PATH = "../../../res/";

#include "../Utils/OS.h"
#include "../Accessors/Resources.h"

ResourceManager::ResourceManager() {
	Resources::m_resources = this;
}

void ResourceManager::loadTexture(std::string _name) {
	addTexture(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".png"));
}
void ResourceManager::unloadTexture(std::string _name) {
	m_textures.erase(_name);
}
void ResourceManager::addTexture(std::string _name, std::string _path) {
	bool success = m_textures[_name].loadFromFile(_path);
}
sf::Texture* ResourceManager::getTexture(std::string _name) {
	//bool success = m_textures.find(_name) != m_textures.end();
	bool success = false;
	if (!success) {
		loadTexture(_name);
		success = m_textures.find(_name) != m_textures.end();
	}
	return &m_textures[_name];
}

void ResourceManager::loadFont(std::string _name) {
	addTexture(_name, OS::getFileInDirectory(TEMP_RES_PATH, _name + ".ttf"));
}
void ResourceManager::unloadFont(std::string _name) {
	m_fonts.erase(_name);
}
void ResourceManager::addFont(std::string _name, std::string _path) {
	bool success = m_fonts[_name].loadFromFile(_path);
}
sf::Font* ResourceManager::getFont(std::string _name) {
	bool success = m_fonts.find(_name) != m_fonts.end();
	if (!success) {
		loadFont(_name);
		success = m_fonts.find(_name) != m_fonts.end();
	}
	return &m_fonts[_name];
}