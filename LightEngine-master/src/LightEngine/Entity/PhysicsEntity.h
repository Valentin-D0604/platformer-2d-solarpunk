#pragma once
#include "Entity.h"
#include "../Collision/Collider.h"
#include "SFML/Graphics.hpp"

class PhysicsEntity : public Entity
{
public:	
	float m_Mass;
	sf::Vector2f m_GravityDirection;
	Collider* m_Collider;

	void setMass(float _mass);
	void setGravityForce(float _gravityForce);
	void setGravityDirection(sf::Vector2f _gravityDirection);

	bool isColliding(PhysicsEntity* _other);
	virtual void onCollision(Entity* _collidedWith) {};

protected:
	float m_GravityForce;
	sf::Vector2f m_Velocity;

private:
	virtual void Update();
	friend class GameManager;
};