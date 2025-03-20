#pragma once
#include "Action.h"
#include "../Entity/Boss.h"

class BossAction_GroundSmash : public Action<Boss>
{
	float m_Timer = 5.0f;
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};

class BossAction_GrabRock : public Action<Boss>
{
	float m_Timer = 5.0f;
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};


class BossAction_Throwing : public Action<Boss>
{
	float m_Timer = 5.0f;
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};

class BossAction_Retreat : public Action<Boss>
{
	float m_Timer = 5.0f;
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};
class BossAction_Idle : public Action<Boss>
{
	float m_idleTimer = 5.0f;
	bool AttackType = 0;
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};

