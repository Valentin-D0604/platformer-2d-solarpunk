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

#include <iostream>
#include <fstream>
#include <string>

void TestScene::OnInitialize()
{
	pEntitySelected = nullptr;
	CreateView();
	SetCameraZoom(1);

	LoadFromText();
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
	std::ifstream fichier("..\\..\\..\\src\\LightEngine\\Map Legend.txt", std::ios::in | std::ios::out);
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
					pEntity1->SetPosition((i * 200), (j * 200), 0.5f, 0.f);
					pEntity1->SetMass(100);
					pEntity1->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '%': {
					monster = CreateEntity<Mob1>();
					monster->SetPosition((i * 200), (j * 200));
					monster->SetMass(100);
					monster->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case 'O': {
					range = CreateEntity<Mob2>();
					range->SetPosition((i * 200), (j * 200));
					range->SetMass(0);
					range->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '+': {
					explode = CreateEntity<Mob3>();
					explode->SetPosition((i * 200), (j * 200));
					explode->SetMass(100);
					explode->SetGravityDirection(sf::Vector2f(0, 1));
					break;
				}
				case '1': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Top1");
					break;
				}
				case '2': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Top2");
					break;
				}
				case '3': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Top3");
					break;
				}
				case '4': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Middle1");
					break;
				}
				case '5': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Middle2");
					break;
				}
				case '6': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Middle3");
					break;
				}
				case '7': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Bottom1");
					break;
				}
				case '8': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Bottom2");
					break;
				}
				case '9': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile1_Bottom3");
					break;
				}
				case 'a': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Top1");
					break;
				}
				case 'b': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Top2");
					break;
				}
				case 'c': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Top3");
					break;
				}
				case 'd': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Middle1");
					break;
				}
				case 'e': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Middle2");
					break;
				}
				case 'f': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Middle3");
					break;
				}
				case 'g': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Bottom1");
					break;
				}
				case 'h': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Bottom2");
					break;
				}
				case 'i': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile2_Bottom3");
					break;
				}
				case 'j': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Top1");
					break;
				}
				case 'k': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Top4");
					break;
				}
				case 'l': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Top2");
					break;
				}
				case 'm': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Top3");
					break;
				}
				case 'n': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Bottom4");
					break;
				}
				case 'o': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Bottom1");
					break;
				}
				case 'p': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Bottom2");
					break;
				}
				case 'q': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Bottom3");
					break;
				}
				case 'C': {
					pPlatform = CreateEntity<Platform>(); // size.x = 204 size.y = 192 mais hitbox 200,200
					pPlatform->SetPosition((i * 200), (j * 200));
					pPlatform->SetTexture("TileMap", "Tile3_Bottom3");
					break;
				}
				default:
					break;
				}
			}
		}
		/*int j = 0;
		std::ifstream fichier("..\\..\\..\\src\\LightEngine\\props.txt", std::ios::in | std::ios::out);
		if (fichier)
		{
			std::string contenu;
			while (std::getline(fichier, contenu))  // tant que l'on peut mettre la ligne dans "contenu"
			{
				j += 1;
				for (int i = 0; i < 100; i++) {
					switch (contenu[i])
					{
					case 'A': {
						Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
						props->SetPosition((i * 200), (j * 200));
						props->SetTexture("Props1", "airs");
						break;
					}
					case 'B': {
						Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
						props->SetPosition((i * 200), (j * 200));
						props->SetTexture("Props1", "signal");
						break;
					}
					case 'V': {
						Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
						props->SetPosition((i * 200), (j * 200));
						props->SetTexture("Props1", "tentacle2");
						break;
					}
					case 'T': {
						Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
						props->SetPosition((i * 200), (j * 200));
						props->SetTexture("Props1", "VineTentacle");
						break;
					}
					case 'H': {
						Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
						props->SetPosition((i * 200), (j * 200));
						props->SetTexture("Props2", "Wind_turbine");
						break;
					}
					case 'M': {
						Props* props = CreateEntity<Props>(); // size.x = 204 size.y = 192 mais hitbox 200,200
						props->SetPosition((i * 200), (j * 200));
						props->SetTexture("Props2", "Mossy_turbine");
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
		}*/
	}
}

Player* TestScene::GetPlayer()
{
	return pEntity1 && pEntity1->IsAlive() ? pEntity1 : nullptr;
}
