#pragma once
#include "Entity.h"
#include "../Collision/Collider.h"
#include "SFML/Graphics.hpp"

class StaticEntity;

class PhysicsEntity : public Entity
{
public:	
	float m_mass;
	sf::Vector2f m_gravityDirection;

	void SetMass(float _mass);
	void SetGravityForce(float _gravityForce);
	void SetGravityDirection(sf::Vector2f _gravityDirection);

	bool IsColliding(PhysicsEntity* _other);
	bool IsColliding(StaticEntity* _other);
	void Repulse(StaticEntity* _other);
	virtual void OnCollision(Entity* _collidedWith) {};

protected:
	float m_gravityForce;
	sf::Vector2f m_velocity;
	Collider* m_collider;
	bool m_physicsCollision;
	virtual void OnFixedUpdate() {};

private:
	virtual void FixedUpdate();
	virtual void Update();
	friend class GameManager;
};