#pragma once
#include "Action.h"
#include "../Entity/Boss.h"

class BossAction_GroundSmash : public Action<Boss>
{
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};

class BossAction_GrabRock : public Action<Boss>
{
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};


class BossAction_Throwing : public Action<Boss>
{
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};

class BossAction_Retreat : public Action<Boss>
{
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};
class BossAction_Idle : public Action<Boss>
{
public:
	void OnStart(Boss* _player) override;
	void OnUpdate(Boss* _player) override;
	void OnEnd(Boss* _player) override;
};

