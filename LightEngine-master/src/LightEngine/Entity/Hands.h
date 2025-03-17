#pragma once

#include "Boss.h"
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Boss;

class Hand : public PhysicsEntity {
private:
    Boss* m_owner;
	bool m_isVulnerable;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void onCollision(Entity* other) override;

	void Stun();
    void PerformSweep();
    void PerformGroundSmash();
    void ThrowRock();
    void RemoveArmor();
    void SetVulnerable(bool vulnerable);

    friend class Boss;

};