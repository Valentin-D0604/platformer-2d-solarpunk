#include <SFML/Graphics.hpp>
#include <iostream>

#include "Managers.h"
#include "Managers/GameManager.h"
#include "SampleScene.h"
#include "TestScene.h"
#include "CollisionSystem.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
	Managers* pInstance = new Managers();

	GET_MANAGER(GameManager)->CreateWindow(1280, 720, "enetre", 60, sf::Color::Black);

	GET_MANAGER(GameManager)->LaunchScene<TestScene>();

	pInstance->run();

	/*CollisionSystem* collisionSystem = new CollisionSystem();

	collisionSystem->test();*/

	return 0;
}