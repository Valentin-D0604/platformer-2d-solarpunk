#include "StaticEntity.h"
#include "../Graphics/Sprite.h"

void StaticEntity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * m_Speed;
	sf::Vector2f translation = distance * m_Direction;
	m_Sprite->move(translation);
	m_Sprite->update();

	m_Collider->setPosition(GetPosition());

	OnUpdate();

	m_Collider->update();
}
