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
#include "../Entity/Props.h"
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
	
}

void TestScene::OnUpdate()
{
	float fps = 1.f / GetDeltaTime();
	std::cout << fps << std::endl;
	if (pEntity1->IsAlive()) SetCameraCenter(pEntity1->GetPosition());
	else {
		SetCameraCenter({ 0,0 });
		SetCameraZoom(5);
		//Destroy();
	//	OnInitialize(); // Need fix with delete
	}
}

void TestScene::Destroy()
{
	pEntity2->Destroy();
	//monster->Destroy();
	//range->Destroy();
	//Explode->Destroy();
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
			for (int i = 0; i < 142; i++) {
				switch (contenu[i])
				{
				case 'P': {
					pEntity1 = CreateEntity<Player>();
					pEntity1->SetPosition((i * 200), (j * 200), 0.5f, 0.f);
					pEntity1->SetMass(100);
					pEntity1->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '%': {
					Mob1* monster = CreateEntity<Mob1>();
					monster->SetPosition((i * 200), (j * 200));
					monster->SetMass(0);
					monster->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case 'O': {
					Mob2* range = CreateEntity<Mob2>();
					range->SetPosition((i * 200), (j * 200));
					range->SetMass(0);
					range->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '+': {
					Mob3* explode = CreateEntity<Mob3>();
					explode->SetPosition((i * 200), (j * 200));
					explode->SetMass(100);
					explode->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '1': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Top1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '2': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Top2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '3': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Top3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '4': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Middle1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '5': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Middle2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '6': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Middle3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '7': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Bottom1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '8': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Bottom2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case '9': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile1_Bottom3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'a': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Top1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'b': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Top2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'c': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Top3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'd': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Middle1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'e': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Middle2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'f': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Middle3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'g': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Bottom1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'h': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Bottom2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'i': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile2_Bottom3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'j': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'k': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top4");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'l': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top2");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'm': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Top3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'n': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom4");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'o': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom1");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'p': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom2");
					pPlatform->SetPosition((i * 200), (j * 200));

					break;
				}
				case 'q': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("TileMap", "Tile3_Bottom3");
					pPlatform->SetPosition((i * 200), (j * 200));
					break;
				}
				case 'C': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetTexture("Props1", "box");
					pPlatform->GetSprite()->setScale(0.75, 0.75);
					pPlatform->SetPosition((i * 200), (j * 200));
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
	return pEntity1 && pEntity1->IsAlive() ? pEntity1 : nullptr;
}
