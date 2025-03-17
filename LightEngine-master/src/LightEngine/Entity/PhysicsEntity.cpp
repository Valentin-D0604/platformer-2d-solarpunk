#include "PhysicsEntity.h"
#include "StaticEntity.h"
#include "../Graphics/Debug.h"
#include "../Utils/Utils.h"
#include "../Graphics/Sprite.h"

#include <iostream>

#define GRAVITATIONNAL_CONSTANT 9.806f
#define MAX_GRAVITATIONNAL_FORCE 500.0f

void PhysicsEntity::Update()
{
	float dt = GetDeltaTime();

	m_GravityForce += m_Mass * dt * GRAVITATIONNAL_CONSTANT;

	m_GravityForce = Utils::Clamp(m_GravityForce, -INFINITY, MAX_GRAVITATIONNAL_FORCE);

	float distance = dt * m_Speed;

	m_Velocity = distance * m_Direction; // Character Input movement
	m_Velocity += m_GravityDirection * m_GravityForce * GetDeltaTime(); // Gravity
	
	sf::Vector2f translation = m_Velocity;
	m_Sprite->move(translation);

	m_Sprite->update();

	m_Collider->setPosition(GetPosition());

	OnUpdate();

	m_Collider->update();
}

void PhysicsEntity::SetMass(float _mass)
{
	m_Mass = _mass;
}

void PhysicsEntity::SetGravityForce(float _gravityForce)
{
	m_GravityForce = _gravityForce;
}

void PhysicsEntity::SetGravityDirection(sf::Vector2f _gravityDirection)
{
	Utils::Normalize(_gravityDirection);
	m_GravityDirection = _gravityDirection;
}

bool PhysicsEntity::IsColliding(PhysicsEntity* _other)
{
	return m_Collider->IsColliding(_other->m_Collider);
}

bool PhysicsEntity::IsColliding(StaticEntity* _other)
{
	return m_Collider->IsColliding(_other->m_Collider);
}

void PhysicsEntity::Repulse(StaticEntity* _other)
{
	if (m_Collider->getShapeTag() == ShapeTag::Rectangle)
	{
		m_Collider->setPosition(GetPosition());
		sf::FloatRect movingBounds(m_Collider->getPosition(0, 0), m_Collider->getPosition(1, 1) - m_Collider->getPosition(0, 0));
		sf::FloatRect staticBounds(_other->m_Collider->getPosition(0, 0), _other->m_Collider->getPosition(1, 1) - _other->m_Collider->getPosition(0, 0));

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
	}
}

