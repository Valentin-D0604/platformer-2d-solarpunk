#pragma once
#include "PhysicsEntity.h"

class Player : public PhysicsEntity
{
	bool jumping;
	float OldY = 0;
public:
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
};


