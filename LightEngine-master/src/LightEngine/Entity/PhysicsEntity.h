#pragma once
#include "Entity.h"
#include "../Collision/Collider.h"
#include "SFML/Graphics.hpp"

class StaticEntity;

class PhysicsEntity : public Entity
{
public:	
	float m_Mass;
	sf::Vector2f m_GravityDirection;

	void SetMass(float _mass);
	void SetGravityForce(float _gravityForce);
	void SetGravityDirection(sf::Vector2f _gravityDirection);

	bool IsColliding(PhysicsEntity* _other);
	bool IsColliding(StaticEntity* _other);
	void Repulse(StaticEntity* _other);
	virtual void OnCollision(Entity* _collidedWith) {};

protected:
	float m_GravityForce;
	sf::Vector2f m_Velocity;
	Collider* m_Collider;
	bool m_physicsCollision;

private:
	virtual void Update();
	friend class GameManager;
};