#pragma once
#include "Entity.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"

class PhysicsEntity : public Entity
{
public:	
	float m_mass;
	sf::Vector2f m_gravityDirection;
	Collider* m_collider;

	void setMass(float _mass);
	void setGravityForce(float _gravityForce);
	void setGravityDirection(sf::Vector2f _gravityDirection);

protected:
	float m_gravityForce;
	sf::Vector2f m_velocity;

private:
	virtual void Update();

	friend class GameManager;
};

