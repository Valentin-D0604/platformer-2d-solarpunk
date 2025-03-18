#include "Mob3Condition.h"

#define DETECTING_RANGE 200.f
#define ATTACK_RANGE  25.f

bool Mob3Condition_IsWalking::OnTest(Mob3* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > DETECTING_RANGE) return true;
    return false;

}

bool Mob3Condition_IsChasing::OnTest(Mob3* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > ATTACK_RANGE && distance <= DETECTING_RANGE)return true;
    return false;
}

bool Mob3Condition_IsAttacking::OnTest(Mob3* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance <= ATTACK_RANGE)return true;
    return false;
}

bool Mob3Condition_IsIdle::OnTest(Mob3* _owner)
{
    return false;
}