#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/View.hpp>

class Scene
{
private:
	GameManager* mp_GameManager;

private:
	void SetGameManager(GameManager* _pGameManager) { mp_GameManager = _pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& _event) = 0;
	virtual void OnUpdate() = 0;

	sf::View* m_view;

public:
	template<typename T>
	T* CreateEntity();

	float GetDeltaTime() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	void CreateView() { m_view = new sf::View; };

	void SetCameraCenter(sf::Vector2f _position);
	sf::Vector2f GetCameraCenter() { return m_view->getCenter(); };

	void SetCameraZoom(float _zoom);

	friend GameManager;
};

#include "Scene.inl"

