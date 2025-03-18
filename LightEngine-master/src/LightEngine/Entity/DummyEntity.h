#pragma once
#include "PhysicsEntity.h"

class DummyEntity : public PhysicsEntity
{
public:
	void OnInitialize() override;
	void OnCollision(Entity* _other) override;
};

