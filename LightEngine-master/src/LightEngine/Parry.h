#pragma once
#include "PhysicsEntity.h"
#include "Scene.h"

class Parry : public PhysicsEntity
{
	float m_parryTime = 0.f;
	float m_maxTime = 2.f;

public : 
	void OnInitialize() override;
	void onCollision(Entity* other) override;
	void OnUpdate() override;
};

