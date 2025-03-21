#include "StaticEntity.h"
#include "../Graphics/Sprite.h"

void StaticEntity::Move(float _x, float _y)
{
	m_sprite->move(_x, _y);
	m_collider->SetPosition(GetPosition());
}

void StaticEntity::FixedUpdate()
{
	float dt = GetDeltaTime();
	float distance = dt * m_Speed;
	sf::Vector2f translation = distance * m_Direction;
	Move(translation.x, translation.y);
}

void StaticEntity::Update()
{
	m_sprite->Update();

	m_collider->Update();

	OnUpdate();
}
