#pragma once
#include "Scene.h"

class PhysicsEntity;
class DummyEntity;
class Player;
class TestScene : public Scene
{
	Player* pEntity1;
	DummyEntity* pEntity2;

	DummyEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


