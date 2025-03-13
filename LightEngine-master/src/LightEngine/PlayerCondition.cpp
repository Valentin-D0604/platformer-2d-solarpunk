#include "PlayerCondition.h"
#include <iostream>

bool PlayerCondition_IsWalking::OnTest(Player* owner)
{
	if (owner->m_velocity.x > 0|| owner->m_velocity.x < 0) {
		return true;
	}
	return false;
}

bool PlayerCondition_IsJumping::OnTest(Player* owner)
{
	if (owner->m_jumping) {
		return true;
	}
	return false;
	//if (!owner->m_jumping) return false;
}

bool PlayerCondition_IsShooting::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_IsParrying::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_IsIdle::OnTest(Player* owner)
{
	if(owner->m_jumping||owner->m_velocity.x != 0) return false;
	return true;
}

bool PlayerCondition_IsDash::OnTest(Player* owner)
{
	return false;
}
