
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Managers.h"
#include "Managers/GameManager.h"
#include "SampleScene.h"
#include "TestScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
	srand(time(NULL));
	Managers* pInstance = new Managers();

	GET_MANAGER(GameManager)->CreateWindow(1280, 720, "enetre", 60, sf::Color::Black);

	GET_MANAGER(GameManager)->LaunchScene<TestScene>();

	pInstance->run();

	return 0;
}