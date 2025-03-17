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
	static Managers* m_Instance;

	GameManager* m_GameManager;
	SceneManager* m_SceneManager;
	ResourceManager* m_ResourceManager;
};

#include "Managers.inl"

