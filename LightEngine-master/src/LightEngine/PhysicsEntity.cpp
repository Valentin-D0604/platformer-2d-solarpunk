#include "PhysicsEntity.h"
#include "Debug.h"
#include "Utils/Utils.h"

#define GRAVITATIONNAL_CONSTANT 9.806f;
#define MAX_GRAVITATIONNAL_FORCE 100.0f;

void PhysicsEntity::Update()
{
	float dt = GetDeltaTime();

	m_gravityForce += m_mass * dt * GRAVITATIONNAL_CONSTANT;

	m_gravityForce = Utils::Clamp(m_gravityForce, -INFINITY, 100.0f); // define doesn't work

	float distance = dt * mSpeed;

	m_velocity = distance * mDirection; // Character Input movement
	m_velocity += m_gravityDirection * m_gravityForce * GetDeltaTime(); // Gravity
	
	sf::Vector2f translation = m_velocity;
	mShape.move(translation);

	if (mTarget.isSet)
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	m_collider->setPosition(GetPosition());

	OnUpdate();

	m_collider->update();
}

void PhysicsEntity::setMass(float _mass)
{
	m_mass = _mass;
}

void PhysicsEntity::setGravityForce(float _gravityForce)
{
	m_gravityForce = _gravityForce;
}

void PhysicsEntity::setGravityDirection(sf::Vector2f _gravityDirection)
{
	Utils::Normalize(_gravityDirection);
	m_gravityDirection = _gravityDirection;
}

bool PhysicsEntity::isColliding(PhysicsEntity* _other)
{
	return m_collider->isColliding(_other->m_collider);
}
