#pragma once

#include "Boss.h"
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Boss;

class Hand : public PhysicsEntity {
private:
    Boss* m_owner;
	bool m_isVulnerable = false;
    bool m_isSweeping = false;
	bool m_isGroundSmashing = false;
	bool m_isThrowing = false;

public:
	void OnInitialize() override;
	void OnUpdate() override;
    void OnCollision(Entity* _collidedWith) override;

	void Stun();
    void PerformSweep();
    void PerformGroundSmash();
    void ThrowRock();
    void RemoveArmor();
    void SetVulnerable(bool _vulnerable);
    
    bool IsSweeping() { return m_isSweeping; }
	bool IsGroundSmashing() { return m_isGroundSmashing; }
	bool IsThrowing() { return m_isThrowing; }
	bool IsStunned() { return m_isVulnerable; }

private:
	friend class Boss;
};