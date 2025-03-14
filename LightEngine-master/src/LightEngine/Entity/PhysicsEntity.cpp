#include "PhysicsEntity.h"
#include "../Graphics/Debug.h"
#include "../Utils/Utils.h"
#include "../Graphics/Sprite.h"

#define GRAVITATIONNAL_CONSTANT 9.806f
#define MAX_GRAVITATIONNAL_FORCE 100.0f

void PhysicsEntity::Update()
{
	float dt = GetDeltaTime();

	m_GravityForce += m_Mass * dt * GRAVITATIONNAL_CONSTANT;

	m_GravityForce = Utils::Clamp(m_GravityForce, -INFINITY, MAX_GRAVITATIONNAL_FORCE); // define doesn't work

	float distance = dt * m_Speed;

	m_Velocity = distance * m_Direction; // Character Input movement
	m_Velocity += m_GravityDirection * m_GravityForce * GetDeltaTime(); // Gravity
	
	sf::Vector2f translation = m_Velocity;
	m_Sprite->move(translation);

	if (m_Target.m_IsSet)
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + m_Direction.x * m_Target.m_Distance;
		float y2 = y1 + m_Direction.y * m_Target.m_Distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(m_Target.m_Position.x, m_Target.m_Position.y, 5.f, sf::Color::Magenta);

		m_Target.m_Distance -= distance;

		if (m_Target.m_Distance <= 0.f)
		{
			SetPosition(m_Target.m_Position.x, m_Target.m_Position.y, 0.5f, 0.5f);
			m_Direction = sf::Vector2f(0.f, 0.f);
			m_Target.m_IsSet = false;
		}
	}

	m_Sprite->update();

	m_Collider->setPosition(GetPosition());

	OnUpdate();

	m_Collider->update();
}

void PhysicsEntity::setMass(float _mass)
{
	m_Mass = _mass;
}

void PhysicsEntity::setGravityForce(float _gravityForce)
{
	m_GravityForce = _gravityForce;
}

void PhysicsEntity::setGravityDirection(sf::Vector2f _gravityDirection)
{
	Utils::Normalize(_gravityDirection);
	m_GravityDirection = _gravityDirection;
}

bool PhysicsEntity::isColliding(PhysicsEntity* _other)
{
	return m_Collider->isColliding(_other->m_Collider);
}
