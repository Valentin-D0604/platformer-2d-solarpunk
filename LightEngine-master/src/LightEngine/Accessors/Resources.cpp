#include "Resources.h"

#include "../Interfaces/IResourceProvider.h"

IResourceProvider* Resources::m_resources = nullptr;

void Resources::loadTexture(std::string _name) {
	m_resources->loadTexture(_name);
}
void Resources::unloadTexture(std::string _name) {
	m_resources->unloadTexture(_name);
}
sf::Texture* Resources::getTexture(std::string _name) {
	return m_resources->getTexture(_name);
}

void Resources::loadFont(std::string _name) {
	m_resources->loadFont(_name);
}
void Resources::unloadFont(std::string _name) {
	m_resources->unloadFont(_name);
}
sf::Font* Resources::getFont(std::string _name) {
	return m_resources->getFont(_name);
}