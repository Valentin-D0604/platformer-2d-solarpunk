#pragma once
#include "Condition.h"
#include "../Entity/Boss.h"

class BossCondition_IsSweeping : public Condition <Boss>
{
public:
	bool OnTest(Boss* owner) override;
};

class BossCondition_IsGroundSmashing : public Condition<Boss>
{
public:
	bool OnTest(Boss* owner) override;
};

class BossCondition_IsThrowing : public Condition<Boss>
{
public:
	bool OnTest(Boss* owner) override;
};

class BossCondition_IsSturnned : public Condition<Boss>
{
public:
	bool OnTest(Boss* owner) override;
};

class BossCondition_IsIdle : public Condition<Boss>
{
public:
	bool OnTest(Boss* owner) override;
};
