#pragma once

#include "Scene.h"

class DummyEntity;

class SampleScene : public Scene
{
	DummyEntity* pEntity1;
	DummyEntity* pEntity2;

	DummyEntity* pEntitySelected;

private:

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


