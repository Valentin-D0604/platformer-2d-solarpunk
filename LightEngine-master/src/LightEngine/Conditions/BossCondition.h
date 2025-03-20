#pragma once
#include "Condition.h"
#include "../Entity/Boss.h"


class BossCondition_IsGroundSmashing : public Condition<Boss>
{
public:
	bool OnTest(Boss* _owner) override;
};

class BossCondition_IsRetreating : public Condition<Boss>
{
public:
	bool OnTest(Boss* _owner) override;
};

class BossCondition_IsThrowing : public Condition<Boss>
{
public:
	bool OnTest(Boss* _owner) override;
};

class BossCondition_IsGrabbingRock : public Condition<Boss>
{
public:
	bool OnTest(Boss* _owner) override;
};

class BossCondition_IsIdle : public Condition<Boss>
{
public:
	bool OnTest(Boss* _owner) override;
};
