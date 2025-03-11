#pragma once

#define GET_MANAGER(type) Managers::get##<type>()

class GameManager;
class SceneManager;
class ResourceManager;

class Managers
{
public:
	Managers();

	template<typename T>
	static T* get();

	void run();

private:
	static Managers* m_instance;

	GameManager* m_gameManager;
	SceneManager* m_sceneManager;
	ResourceManager* m_resourceManager;
};

#include "Managers.inl"

