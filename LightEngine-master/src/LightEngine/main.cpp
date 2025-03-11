
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
	Managers* pInstance = new Managers();

	GET_MANAGER(GameManager)->CreateWindow(1280, 720, "SampleScene", 60, sf::Color::Black);

	GET_MANAGER(GameManager)->LaunchScene<SampleScene>();

	pInstance->run();

	return 0;
}