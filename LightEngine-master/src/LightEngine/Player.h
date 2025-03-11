#pragma once
#include "PhysicsEntity.h"
#include "Parry.h"
#define MAX_VELOCITY 400

class Player : public PhysicsEntity
{
	bool jumping;
	float OldY = 0;
	sf::Vector2f velocity; 
	float acceleration = 600.0f;
	float friction = 400.0f; 
	float airResistance = 100.0f; 
public:
	void OnInitialize() override;
	void onCollision(Entity* other) override;
	void OnUpdate() override;

	void parry();
};


