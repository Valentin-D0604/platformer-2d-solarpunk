#pragma once

#include "Boss.h"
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Boss;

class Hand : public PhysicsEntity {
private:
    Boss* m_owner;
    bool m_isLeft;
    bool m_isSweeping = false;
    bool m_isGroundSmashing = false;
    bool m_isThrowing = false;
    bool m_isVulnerable = false;
    float m_timer = 0.0f;

public:
    
    Hand(bool isLeft);

    void OnInitialize() override;
    void OnUpdate() override;
    void OnCollision(Entity* _collidedWith) override;

    void Sweep();
    void GroundSmash();
    void HandleStun();
 
    
    void Stop();
    void Idle();
	void PickUpRock();
	
    
    bool IsTouchingGround();
	bool IsSweeping() { return m_isSweeping; }
	bool IsGroundSmashing() { return m_isGroundSmashing; }
	bool IsThrowing() { return m_isThrowing; }
	bool IsVulnerable() { return m_isVulnerable; }

	void SetSweeping(bool _sweeping) { m_isSweeping = _sweeping; }
	void SetGroundSmashing(bool _groundSmashing) { m_isGroundSmashing = _groundSmashing; }
	void SetThrowing(bool _throwing) { m_isThrowing = _throwing; }
	void SetVulnerable(bool _vulnerable) { m_isVulnerable = _vulnerable; }
    void SetOwner(Boss* _owner) { m_owner = _owner; }

    void Stun() { m_isVulnerable = true; m_timer = 3.0f; }
    void PerformSweep() {m_isSweeping = true; m_timer = 2.0f; }
    void PerformGroundSmash() { m_isGroundSmashing = true; }
    void ThrowRock() { m_isThrowing = true; m_timer = 1.5f; }
    void RemoveArmor() { m_isVulnerable = false; }
	
    Boss* GetOwner() { return m_owner; }
};