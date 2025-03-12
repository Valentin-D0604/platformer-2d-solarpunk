#include "Mob1Condition.h"

bool Mob1Condition_IsWalking::OnTest(Mob1* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance > 300.f) return true;
    return false;
    
}

bool Mob1Condition_IsChasing::OnTest(Mob1* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if (distance > 50.0f && distance <= 300.f)return true;
    return false;
}

bool Mob1Condition_IsAttacking::OnTest(Mob1* owner)
{
    float distance = owner->GetDistanceToPlayer();
    if( distance <= 50.0f)return true;
    return false;
}

bool Mob1Condition_IsIdle::OnTest(Mob1* owner)
{
    return false;
}