#include "Resources.h"

#include "../Interfaces/IResourceProvider.h"

IResourceProvider* Resources::m_Resources = nullptr;

void Resources::loadTexture(std::string _name) {
	m_Resources->loadTexture(_name);
}
void Resources::unloadTexture(std::string _name) {
	m_Resources->unloadTexture(_name);
}
sf::Texture* Resources::getTexture(std::string _name) {
	return m_Resources->getTexture(_name);
}

void Resources::loadFont(std::string _name) {
	m_Resources->loadFont(_name);
}
void Resources::unloadFont(std::string _name) {
	m_Resources->unloadFont(_name);
}
sf::Font* Resources::getFont(std::string _name) {
	return m_Resources->getFont(_name);
}