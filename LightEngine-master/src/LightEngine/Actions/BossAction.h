#pragma once
#include "Action.h"
#include "../Entity/Boss.h"

class BossAction_Sweeping : public Action<Boss>
{
	sf::Vector2f dir = { 1,0 };
public:
	void OnStart(Boss* player) override;
	void OnUpdate(Boss* player) override;
	void OnEnd(Boss* player) override;
};

class BossAction_GroundSmash : public Action<Boss>
{
public:
	void OnStart(Boss* player) override;
	void OnUpdate(Boss* player) override;
	void OnEnd(Boss* player) override;
};

class BossAction_Throwing : public Action<Boss>
{
public:
	void OnStart(Boss* player) override;
	void OnUpdate(Boss* player) override;
	void OnEnd(Boss* player) override;
};

class BossAction_Stunned : public Action<Boss>
{
public:
	void OnStart(Boss* player) override;
	void OnUpdate(Boss* player) override;
	void OnEnd(Boss* player) override;
};

class BossAction_Idle : public Action<Boss>
{
public:
	void OnStart(Boss* player) override;
	void OnUpdate(Boss* player) override;
	void OnEnd(Boss* player) override;
};

