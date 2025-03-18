#include "Resources.h"

#include "../Interfaces/IResourceProvider.h"

IResourceProvider* Resources::m_resources = nullptr;

void Resources::LoadTexture(std::string _name) {
	m_resources->LoadTexture(_name);
}
void Resources::UnloadTexture(std::string _name) {
	m_resources->UnloadTexture(_name);
}
sf::Texture* Resources::GetTexture(std::string _name) {
	return m_resources->GetTexture(_name);
}

void Resources::LoadFont(std::string _name) {
	m_resources->LoadFont(_name);
}
void Resources::UnloadFont(std::string _name) {
	m_resources->UnloadFont(_name);
}
sf::Font* Resources::GetFont(std::string _name) {
	return m_resources->GetFont(_name);
}