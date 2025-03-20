#include "HUD.h"
#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"

void HUD::OnInitialize() {
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Pv_Full")));
}

void HUD::OnUpdate() {
	
}

void HUD::InitText(const char* _textureName,sf::Vector2f pos) {
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture(_textureName)));
	SetPosition(pos.x,pos.y);
}