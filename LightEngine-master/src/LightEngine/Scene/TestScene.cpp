#include "../Scene/TestScene.h"


#include "../Graphics/Debug.h"
#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"

#include "../Entity/DummyEntity.h"
#include "../Entity/Player.h"
#include "../Entity/Mob1.h"
#include "../Entity/Mob2.h"
#include "../Entity/Mob3.h"
#include "../Entity/Platform.h"
#include "../Entity/Background.h"


#include <iostream>
#include <fstream>
#include <string>

void TestScene::OnInitialize()
{
	pEntitySelected = nullptr;
	CreateView();
	SetCameraZoom(1);

	LoadFromText();

	CreateBackgroundEntity<Background>()->SetPlayer(pEntity1);
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
	//	TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void TestScene::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	if (pEntity1->IsAlive()) SetCameraCenter(pEntity1->GetPosition());
	else {
		SetCameraCenter({ 0,0 });
		SetCameraZoom(5);
		//Destroy();
		OnInitialize(); // Need fix with delete
	}
}

void TestScene::Destroy()
{
	pEntity2->Destroy();
	monster->Destroy();
	//range->Destroy();
	//Explode->Destroy();
}

void TestScene::LoadFromText()
{
	int j = 0;
	std::ifstream fichier("..\\..\\..\\src\\LightEngine\\edit.txt", std::ios::in | std::ios::out);
	if (fichier)
	{
		std::string contenu;
		while (std::getline(fichier, contenu))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			j += 1;
			for (int i = 0; i < 100; i++) {
				switch (contenu[i])
				{
				case 'P': {
					pEntity1 = CreateEntity<Player>();
					pEntity1->SetPosition((i*204), (j*192), 0.5f, 0.f);
					pEntity1->SetMass(100);
					pEntity1->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '+': {
					explode = CreateEntity<Mob3>();
					explode->SetPosition((i * 204), (j * 192));
					explode->SetMass(100);
					explode->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case 'O': {
					range = CreateEntity<Mob2>();
					range->SetPosition((i * 204), (j * 192));
					range->SetMass(0);
					range->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '%': {
					monster = CreateEntity<Mob1>();
					monster->SetPosition((i * 204), (j * 192));
					monster->SetMass(100);
					monster->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '$': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 204), (j * 192));
					break;
				}
				default:
					break;
				}
			}
		}
	}
	else {
		std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
	}
}

Player* TestScene::GetPlayer()
{
	return pEntity1 && pEntity1->IsAlive() ? pEntity1 : nullptr;
}
