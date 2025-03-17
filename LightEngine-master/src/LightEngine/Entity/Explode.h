#pragma once
#include "../Entity/PhysicsEntity.h"

class Explode : public PhysicsEntity
{
	float m_duration = 0.1f;
	float m_DamageCooldown = 0.f;
public:
	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
};


