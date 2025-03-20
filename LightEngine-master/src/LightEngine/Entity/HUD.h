#pragma once
#include "../Entity/Entity.h"

class HUD : public Entity
{
public : 
	void OnInitialize() override;
	void OnUpdate() override;
	void InitText(const char* _textureName, sf::Vector2f pos);
};

