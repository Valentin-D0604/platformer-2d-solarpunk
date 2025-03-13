#include "Mob2Condition.h"

#define DETECTING_RANGE 50.f
#define ATTACK_RANGE  500.f

bool Mob2Condition_IsWalking::OnTest(Mob2* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance > DETECTING_RANGE) return true;
    return false;

}

bool Mob2Condition_IsChasing::OnTest(Mob2* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance > ATTACK_RANGE && distance <= DETECTING_RANGE)return true;
    return false;
}

bool Mob2Condition_IsAttacking::OnTest(Mob2* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance <= ATTACK_RANGE)return true;
    return false;
}

bool Mob2Condition_IsIdle::OnTest(Mob2* owner)
{
    return false;
}