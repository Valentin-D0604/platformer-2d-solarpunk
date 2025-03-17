#include "BossCondition.h"
#define DETECTING_RANGE 300.f
#define ATTACK_RANGE  50.f

bool BossCondition_IsSweeping::OnTest(Boss* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > DETECTING_RANGE) return true;
    return false;
}

bool BossCondition_IsGroundSmashing::OnTest(Boss* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > ATTACK_RANGE && distance <= DETECTING_RANGE)return true;
    return false;
}

bool BossCondition_IsThrowing::OnTest(Boss* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance <= ATTACK_RANGE)return true;
    return false;
}

bool BossCondition_IsIdle::OnTest(Boss* _owner)
{
	return true;
}

bool BossCondition_IsStunned::OnTest(Boss* _owner)
{
	return _owner->IsStunned();
}
