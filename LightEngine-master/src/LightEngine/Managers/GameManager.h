#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity;
class PhysicsEntity;
class StaticEntity;
class Scene;
class Debug;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> m_entities;
	std::list<PhysicsEntity*> m_physicsEntities;
	std::list<StaticEntity*> m_staticEntities;
	std::list<Entity*> m_entitiesToDestroy;
	std::list<Entity*> m_entitiesToAdd;

	sf::RenderWindow* mp_Window;
	sf::Font m_font;

	Scene* mp_Scene;

	float m_deltaTime;
	float m_timeSinceFixed;

	int m_windowWidth;
	int m_windowHeight;

	sf::Color m_clearColor;

private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Clear();
	void FixedUpdate();
	void Update();
	void Draw();

	void SetDeltaTime(float _deltaTime) { m_deltaTime = _deltaTime; }

	sf::RenderWindow* GetWindow() const { return mp_Window; }

public:
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int _width, unsigned int _height, const char* _title, int _fpsLimit = 60, sf::Color _clearColor = sf::Color::Black);

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return m_deltaTime; }
	Scene* GetScene() const { return mp_Scene; }
	sf::Font& GetFont() { return m_font; };

	friend Debug;
	friend Scene;
	friend class Managers;
};

#include "GameManager.inl"