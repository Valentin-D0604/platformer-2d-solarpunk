#pragma once
#include "../Entity/PhysicsEntity.h"

class Explode : public PhysicsEntity
{
	float m_DamageCooldown = 0.f;
public:
	void OnInitialize() override;
	void OnCollision(Entity* _other) override;
	void OnUpdate() override;
	void OnAnimationEnd(const std::string& _animationIndex) override;
};


