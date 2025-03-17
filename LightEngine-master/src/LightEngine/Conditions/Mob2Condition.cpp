#include "Mob2Condition.h"

#define DETECTING_RANGE 400.f
#define ATTACK_RANGE  300.f

bool Mob2Condition_IsWalking::OnTest(Mob2* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > DETECTING_RANGE) return true;
    return false;

}

bool Mob2Condition_IsChasing::OnTest(Mob2* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > ATTACK_RANGE && distance <= DETECTING_RANGE)return true;
    return false;
}

bool Mob2Condition_IsAttacking::OnTest(Mob2* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance <= ATTACK_RANGE)return true;
    return false;
}

bool Mob2Condition_IsIdle::OnTest(Mob2* _owner)
{
    return false;
}