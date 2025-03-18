#include "StaticEntity.h"
#include "../Graphics/Sprite.h"

void StaticEntity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * m_Speed;
	sf::Vector2f translation = distance * m_Direction;
	m_sprite->move(translation);
	m_sprite->Update();

	m_collider->SetPosition(GetPosition());

	OnUpdate();

	m_collider->Update();
}
