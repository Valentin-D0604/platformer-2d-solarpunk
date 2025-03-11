#pragma once
#include "PhysicsEntity.h"

class Player : public PhysicsEntity
{
	bool jumping;
	float OldY = 0;
public:
	void OnInitialize() override;
	void onCollision(Entity* other) override;
	void OnUpdate() override;

	void Parry();
};


