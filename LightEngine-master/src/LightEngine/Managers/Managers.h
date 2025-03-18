#pragma once

#define GET_MANAGER(type) Managers::Get##<type>()

class GameManager;
class SceneManager;
class ResourceManager;

class Managers
{
public:
	Managers();

	template<typename T>
	static T* Get();

	void Run();

private:
	static Managers* m_instance;

	GameManager* m_gameManager;
	SceneManager* m_sceneManager;
	ResourceManager* m_resourceManager;
};

#include "Managers.inl"

