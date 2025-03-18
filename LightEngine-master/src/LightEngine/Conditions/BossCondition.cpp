#include "BossCondition.h"

bool BossCondition_IsSweeping::OnTest(Boss* _owner)
{
	return _owner->IsSweepping();
}

bool BossCondition_IsGroundSmashing::OnTest(Boss* _owner)
{
	return _owner->IsGroundSmashing();
}

bool BossCondition_IsThrowing::OnTest(Boss* _owner)
{
	return _owner->IsThrowing();
}

bool BossCondition_IsStunned::OnTest(Boss* _owner)
{
	return _owner->IsStunned();
}

bool BossCondition_IsIdle::OnTest(Boss* _owner)
{
	return !_owner->IsSweepping() && !_owner->IsGroundSmashing() && !_owner->IsThrowing();
}