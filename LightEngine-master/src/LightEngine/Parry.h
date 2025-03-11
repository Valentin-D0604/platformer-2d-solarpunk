#pragma once
#include "PhysicsEntity.h"
#include "Scene.h"

class Parry : public PhysicsEntity
{
	float ParryTime = 0.f;
	float MaxTime = 2.f;

public : 
	void OnInitialize() override;
	void onCollision(Entity* other) override;
	void OnUpdate() override;
};

