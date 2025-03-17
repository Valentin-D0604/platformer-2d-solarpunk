#include "Mob1Condition.h"
#define DETECTING_RANGE 300.f
#define ATTACK_RANGE  50.f

bool Mob1Condition_IsWalking::OnTest(Mob1* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > DETECTING_RANGE) return true;
    return false;
    
}

bool Mob1Condition_IsChasing::OnTest(Mob1* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if (distance > ATTACK_RANGE && distance <= DETECTING_RANGE)return true;
    return false;
}

bool Mob1Condition_IsAttacking::OnTest(Mob1* _owner)
{
    float distance = _owner->GetDistanceToPlayer();
    if( distance <= ATTACK_RANGE)return true;
    return false;
}

bool Mob1Condition_IsIdle::OnTest(Mob1* _owner)
{
    return false;
}