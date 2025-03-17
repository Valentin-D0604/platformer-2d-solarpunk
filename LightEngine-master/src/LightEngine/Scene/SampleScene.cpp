#include "SampleScene.h"

#include "../Entity/DummyEntity.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>();
	pEntity1->SetPosition(100, 100);

	pEntity2 = CreateEntity<DummyEntity>();
	pEntity2->SetPosition(500, 500);

	pEntitySelected = nullptr;

	GET_MANAGER(ResourceManager)->loadTexture("test");
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{

	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr) 
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void SampleScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}