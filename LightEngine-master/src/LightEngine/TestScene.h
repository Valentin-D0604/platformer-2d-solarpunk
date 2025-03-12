#pragma once
#include "Scene.h"

class PhysicsEntity;
class DummyEntity;
class Player;
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
	Platform* pPlatform;

	Entity* pEntitySelected;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void GetTag() { return; }
};


