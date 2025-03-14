#pragma once
#include "Scene.h"

class PhysicsEntity;
class DummyEntity;
class Player;
class Mob1;
class Platform;

class TestScene : public Scene
{
public:

	enum Tag
	{
		PLAYER,
		ENEMY,
		OBJECT
	};

	Player* pEntity1;
	DummyEntity* pEntity2;
	Mob1* monster;
	Platform* pPlatform;

	Entity* pEntitySelected;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	enum Tag
	{
		player,
		mob1,
		bullet
	};

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	
	Player* GetPlayer();

	void GetTag() { return; }
};


