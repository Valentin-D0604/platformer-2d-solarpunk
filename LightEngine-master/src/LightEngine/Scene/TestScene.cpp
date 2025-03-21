#include "../Scene/TestScene.h"


#include "../Graphics/Debug.h"

#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"

#include "../Entity/DummyEntity.h"
#include "../Entity/Player.h"
#include "../Entity/Mob1.h"
#include "../Entity/Mob2.h"
#include "../Entity/Mob3.h"
#include "../Entity/Boss.h"
#include "../Entity/Platform.h"
#include "../Entity/Background.h"
#include "../Entity/Overlay.h"
#include "../Entity/Props.h"

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
}

void TestScene::OnUpdate()
{

	float fps = 1.f / GetDeltaTime();
	std::cout << fps << std::endl;
	
	if (m_player->IsAlive())
	{
		SetCameraCenter(m_player->GetPosition());
		Debug::DrawText(m_player->GetPosition().x - GetWindowWidth()/2, m_player->GetPosition().y - GetWindowHeight()/2, "FPS: " + std::to_string(fps), sf::Color::Blue);

	}
	else {
		SetCameraCenter({ 0,0 });
		SetCameraZoom(5);
		//Destroy();
	//	OnInitialize(); // Need fix with delete
	}
}

void TestScene::Destroy()
{
	
}

void TestScene::LoadFromText()
{
	int j = 0;
	std::ifstream fichier("..\\..\\..\\src\\LightEngine\\ppppp.txt", std::ios::in | std::ios::out);
	if (fichier)
	{
		std::string contenu;
		while (std::getline(fichier, contenu))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			j += 1;
			for (int i = 0; i < 122; i++) {
				switch (contenu[i])
				{
				case 'P': 
				{
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
				case '$': 
				{
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 204), (j * 192));
				}

				case '1': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Top1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '2': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Top2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '3': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Top3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '4': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Middle1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '5': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Middle2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '6': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Middle3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '7': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Bottom1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '8': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Bottom2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '9': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Bottom3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'a': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Top1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'b': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Top2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'c': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Top3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'd': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Middle1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'e': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Middle2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'f': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Middle3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'g': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Bottom1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'h': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Bottom2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'i': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Bottom3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'j': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'k': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top4");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'l': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'm': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'n': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom4");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'o': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'p': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom2");
					pPlatform->SetPosition((i * 200), (j * 200));

					break;
				}
				case 'q': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'C': {
					Platform* pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("Props1", "box");
					pPlatform->GetSprite()->setScale(0.75, 0.75);
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '*': {
					Boss* boss = CreateEntity<Boss>();
					boss->SetPosition((i * 200), (j * 200),0.5,0.5);
					break;
				}
				default:
					break;
				}
			}
		}
	}
	
	int k = 0;
	std::ifstream worldProps("..\\..\\..\\src\\LightEngine\\props.txt", std::ios::in | std::ios::out);
	if (worldProps)
	{
		std::string contenu;
		while (std::getline(worldProps, contenu))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			k += 1;
			for (int i = 0; i < 100; i++) {
				switch (contenu[i])
				{
				case 'A': {
					Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					props->SetTexture("Props1", "airs");
					props->SetPosition((i * 200), (k * 200));
					break;
				}
				case 'B': {
					Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					props->SetTexture("Props1", "signal");
					props->SetPosition((i * 200), (k * 200));
					break;
				}
				case 'V': {
					Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					props->SetTexture("Props1", "tentacle2");
					props->SetPosition((i * 200), (k * 200));
					break;
				}
				case 'T': {
					Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					props->SetTexture("Props1", "VineTentacle");
					props->SetPosition((i * 200), (k * 200));
					break;
				}
				case 'H': {
					Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					props->SetTexture("Props2", "Wind_turbine");
					props->SetPosition((i * 200), (k * 200));
					break;
				}
				case 'M': {
					Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					props->SetTexture("Props2", "Mossy_turbine");
					props->SetPosition((i * 200), (k * 200));
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
