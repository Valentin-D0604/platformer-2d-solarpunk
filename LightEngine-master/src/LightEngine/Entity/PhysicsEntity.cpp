#include "PhysicsEntity.h"
#include "StaticEntity.h"
#include "../Graphics/Debug.h"
#include "../Utils/Utils.h"
#include "../Graphics/Sprite.h"

#include <iostream>

#define GRAVITATIONNAL_CONSTANT 9.806f
#define MAX_GRAVITATIONNAL_FORCE 500.0f

void PhysicsEntity::FixedUpdate()
{
	//float dt = GetDeltaTime();

	float dt = 1.0f / 60.0f;

	m_gravityForce += m_mass * dt * GRAVITATIONNAL_CONSTANT;

	m_gravityForce = Utils::Clamp(m_gravityForce, -INFINITY, MAX_GRAVITATIONNAL_FORCE);

	float distance = dt * m_Speed;

	m_velocity = distance * m_Direction; // Character Input movement
	m_velocity += m_gravityDirection * m_gravityForce * GetDeltaTime(); // Gravity

	sf::Vector2f translation = m_velocity;
	m_sprite->move(translation);

	m_collider->SetPosition(GetPosition());

	OnFixedUpdate();
}

void PhysicsEntity::Update()
{
	m_sprite->Update();

	OnUpdate();

	m_collider->Update();
}

void PhysicsEntity::SetMass(float _mass)
{
	m_mass = _mass;
}

void PhysicsEntity::SetGravityForce(float _gravityForce)
{
	m_gravityForce = _gravityForce;
}

void PhysicsEntity::SetGravityDirection(sf::Vector2f _gravityDirection)
{
	Utils::Normalize(_gravityDirection);
	m_gravityDirection = _gravityDirection;
}

bool PhysicsEntity::IsColliding(PhysicsEntity* _other)
{
	return m_collider->IsColliding(_other->m_collider);
}

bool PhysicsEntity::IsColliding(StaticEntity* _other)
{
	return m_collider->IsColliding(_other->m_collider);
}

void PhysicsEntity::Repulse(StaticEntity* _other)
{
	if (m_collider->GetShapeTag() == ShapeTag::rectangle)
	{
		m_collider->SetPosition(GetPosition());
		sf::FloatRect movingBounds(m_collider->GetPosition(0, 0), m_collider->GetPosition(1, 1) - m_collider->GetPosition(0, 0));
		sf::FloatRect staticBounds(_other->m_collider->GetPosition(0, 0), _other->m_collider->GetPosition(1, 1) - _other->m_collider->GetPosition(0, 0));

		float overlapLeft = movingBounds.left + movingBounds.width - staticBounds.left;
		float overlapRight = staticBounds.left + staticBounds.width - movingBounds.left;
		float overlapTop = movingBounds.top + movingBounds.height - staticBounds.top;
		float overlapBottom = staticBounds.top + staticBounds.height - movingBounds.top;

		bool fromLeft = overlapLeft < overlapRight;
		bool fromTop = overlapTop < overlapBottom;

		float minOverlapX = fromLeft ? overlapLeft : overlapRight;
		float minOverlapY = fromTop ? overlapTop : overlapBottom;

		// Repousser dans la direction la plus courte (horizontale ou verticale)
		if (minOverlapX < minOverlapY)
		{
			Move(fromLeft ? -minOverlapX : minOverlapX, 0);
		}
		else
		{
			Move(0, fromTop ? -minOverlapY : minOverlapY);
		}
		m_collider->SetPosition(GetPosition());
	}
}

