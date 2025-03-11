#pragma once
#include "PhysicsEntity.h"

class DummyEntity : public PhysicsEntity
{
public:
	void onCollision(Entity* other) override;
};

