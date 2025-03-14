#include "PlayerCondition.h"
#include <iostream>

bool PlayerCondition_IsWalking::OnTest(Player* _owner)
{
	if (_owner->m_Velocity.x > 0|| _owner->m_Velocity.x < 0) {
		return true;
	}
	return false;
}

bool PlayerCondition_IsJumping::OnTest(Player* _owner)
{
	if (_owner->m_Jumping) {
		return true;
	}
	return false;
	//if (!owner->m_jumping) return false;
}

bool PlayerCondition_IsShooting::OnTest(Player* _owner)
{
	return false;
}

bool PlayerCondition_IsParrying::OnTest(Player* _owner)
{
	return false;
}

bool PlayerCondition_IsIdle::OnTest(Player* _owner)
{
	if(_owner->m_Jumping||_owner->m_Velocity.x != 0) return false;
	return true;
}