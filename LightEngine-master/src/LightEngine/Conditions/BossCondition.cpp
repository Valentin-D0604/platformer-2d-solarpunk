#include "BossCondition.h"

bool BossCondition_IsGroundSmashing::OnTest(Boss* _owner)
{
	return _owner->IsGroundSmashing();
}

bool BossCondition_IsRetreating::OnTest(Boss* _owner)
{
	return _owner->IsRetreating();
}

bool BossCondition_IsThrowing::OnTest(Boss* _owner)
{
	return _owner->IsThrowing();
}

bool BossCondition_IsIdle::OnTest(Boss* _owner)
{
	bool toreturn = false;
	if (!_owner->IsGrabbingRock() || !_owner->IsGroundSmashing() || !_owner->IsRetreating() || !_owner->IsThrowing())	{toreturn = true;}
	return toreturn;
}

bool BossCondition_IsGrabbingRock::OnTest(Boss* _owner)
{
	return _owner->IsGrabbingRock();
}
