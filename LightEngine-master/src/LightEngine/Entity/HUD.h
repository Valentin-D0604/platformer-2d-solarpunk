#pragma once
#include "../Entity/Entity.h"

class HUD : public Entity
{
	sf::Vector2f m_Pos;
	int number = 0;
public : 
	void OnInitialize() override;
	void OnUpdate() override;
	void InitText(const char* _textureName, sf::Vector2f pos);
	void SetPos(int i);
};

