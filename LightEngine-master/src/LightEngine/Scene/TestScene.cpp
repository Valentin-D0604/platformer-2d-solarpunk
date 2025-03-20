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
#include "../Entity/Overlay.h"


#include <iostream>
#include <fstream>
#include <string>

void TestScene::OnInitialize()
{
	CreateView();
	SetCameraZoom(1);

	LoadFromText();

	CreateBackgroundEntity<Background>()->SetPlayer(m_player);
	m_overlay = CreateEntity<Overlay>(); 
	m_overlay->SetPlayer(m_player);
	m_overlay->FadeInOut(5, 5);
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;
}

void TestScene::OnUpdate()
{
	if (m_player->IsAlive()) SetCameraCenter(m_player->GetPosition());
	else {
		SetCameraCenter({ 0,0 });
		SetCameraZoom(5);
		//Destroy();
		OnInitialize(); // Need fix with delete
	}
}

void TestScene::Destroy()
{
	
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
					m_player = CreateEntity<Player>();
					m_player->SetPosition((i*204), (j*192), 0.5f, 0.f);
					m_player->SetMass(100);
					m_player->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '+': {
					Mob3* explode = CreateEntity<Mob3>();
					explode->SetPosition((i * 204), (j * 192));
					explode->SetMass(100);
					explode->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case 'O': {
					Mob2* range = CreateEntity<Mob2>();
					range->SetPosition((i * 204), (j * 192));
					range->SetMass(0);
					range->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '%': {
					Mob1* monster = CreateEntity<Mob1>();
					monster->SetPosition((i * 204), (j * 192));
					monster->SetMass(100);
					monster->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '$': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
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
	return m_player && m_player->IsAlive() ? m_player : nullptr;
}
