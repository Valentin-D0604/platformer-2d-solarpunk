#pragma once
#include "Action.h"
#include "Player.h"

class PlayerAction_Walking : public Action<Player>
{
public:
	void OnStart(Player* player) override;
	void OnUpdate(Player* player) override;
	void OnEnd(Player* player) override;
};

class PlayerAction_jumping : public Action<Player>
{
public:
	void OnStart(Player* player) override;
	void OnUpdate(Player* player) override;
	void OnEnd(Player* player) override;
};


class PlayerAction_Shooting : public Action<Player>
{
public:
	void OnStart(Player* player) override;
	void OnUpdate(Player* player) override;
	void OnEnd(Player* player) override;
};

class PlayerAction_Parrying : public Action<Player>
{
public:
	void OnStart(Player* player) override;
	void OnUpdate(Player* player) override;
	void OnEnd(Player* player) override;
};

class PlayerAction_Idle : public Action<Player>
{
public:
	void OnStart(Player* player) override;
	void OnUpdate(Player* player) override;
	void OnEnd(Player* player) override;
};
