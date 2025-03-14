#include "BossCondition.h"
#define DETECTING_RANGE 300.f
#define ATTACK_RANGE  50.f

bool BossCondition_IsSweeping::OnTest(Boss* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance > DETECTING_RANGE) return true;
    return false;
}

bool BossCondition_IsGroundSmashing::OnTest(Boss* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance > ATTACK_RANGE && distance <= DETECTING_RANGE)return true;
    return false;
}

bool BossCondition_IsThrowing::OnTest(Boss* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance <= ATTACK_RANGE)return true;
    return false;
}

bool BossCondition_IsIdle::OnTest(Boss* owner)
{
    return false;
}
