#include "HUD.h"
#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"
#include "../Scene/TestScene.h"
#include "Player.h"
#include <iostream>

void HUD::OnInitialize() {
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Pv_Full")));	
}

void HUD::OnUpdate() {
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();
	if (player == nullptr) return;
	sf::Vector2f Pos = player->GetPosition();
	SetPosition({ Pos.x+ 950 +(200* number) ,Pos.y + 300});
}

void HUD::InitText(const char* _textureName,sf::Vector2f pos) {
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture(_textureName)));
	m_sprite->setScale(0.05, 0.05);
	std::cout << _textureName << " " << GetPosition().x << " " << GetPosition().y << std::endl;
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	SetPosition(pos.x,pos.y);
}

void HUD::SetPos(int i)
{
	number = i;
}
