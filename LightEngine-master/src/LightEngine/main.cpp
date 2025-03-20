#include <SFML/Graphics.hpp>
#include <iostream>

#include "Managers/Managers.h"
#include "Managers/GameManager.h"

#include "Scene/SampleScene.h"
#include "Scene/TestScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
	srand(time(NULL));
	Managers* pInstance = new Managers();

	GET_MANAGER(GameManager)->CreateWindow(1280, 720, "enetre", 6000, sf::Color::Black);

	GET_MANAGER(GameManager)->LaunchScene<TestScene>();

	pInstance->Run();

	return 0;
}