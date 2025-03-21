#include "GameManager.h"

#include "../Entity/Entity.h"
#include "../Entity/PhysicsEntity.h"
#include "../Entity/StaticEntity.h"
#include "../Graphics/Debug.h"
#include "../Graphics/Sprite.h"
#include "Managers.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

GameManager::GameManager()
{
	mp_Window = nullptr;
	m_deltaTime = 0.0f;
	mp_Scene = nullptr;
	m_windowWidth = -1;
	m_windowHeight = -1;
	m_font = *(GET_MANAGER(ResourceManager)->GetFont("Hack-Regular"));
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mp_Window;
	delete mp_Scene;

	for (Entity* entity : m_entities)
	{
		delete entity;
	}
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mp_Window == nullptr);

	mp_Window = new sf::RenderWindow(sf::VideoMode(width, height), title);//,sf::Style::Fullscreen
	mp_Window->setFramerateLimit(fpsLimit);

	m_windowWidth = width;
	m_windowHeight = height;

	m_clearColor = clearColor;
}

void GameManager::Run()
{
	if (mp_Window == nullptr) 
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}

	//#TODO : Load somewhere else
	bool fontLoaded = m_font.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	_ASSERT(mp_Scene != nullptr);

	sf::Clock clock;
	while (mp_Window->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput();

		m_timeSinceFixed += m_deltaTime;

		if (m_timeSinceFixed >= 1.f / 60.f)
		{
			FixedUpdate();
			m_timeSinceFixed = 0;
		}

		Update();
		
		Draw();
	}
}

void GameManager::HandleInput()
{
	sf::Event event;
	while (mp_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mp_Window->close();
		}

		mp_Scene->OnEvent(event);
	}
}

void GameManager::Clear()
{

}

void GameManager::Update()
{
	std::cout << "Update" << std::endl;
	mp_Scene->OnUpdate();

    //Update
    for (auto it = m_entities.begin(); it != m_entities.end(); )
    {
		Entity* entity = *it;

        entity->Update();

        if (entity->ToDestroy() == false)
        {
            ++it;
            continue;
        }

        m_entitiesToDestroy.push_back(entity);
        
		PhysicsEntity* physEntity = dynamic_cast<PhysicsEntity*>(*it);
		if (physEntity != nullptr)
		{
			m_physicsEntities.erase(std::find(m_physicsEntities.begin(), m_physicsEntities.end(), physEntity));
		}

		else
		{
			StaticEntity* staticEntity = dynamic_cast<StaticEntity*>(*it);
			if (staticEntity != nullptr)
			{
				m_staticEntities.erase(std::find(m_staticEntities.begin(), m_staticEntities.end(), staticEntity));
			}
		}

		it = m_entities.erase(it);
    }

	for (auto it = m_entitiesToDestroy.begin(); it != m_entitiesToDestroy.end(); ++it) 
	{
		delete *it;
	}

    m_entitiesToDestroy.clear();

	for (auto it = m_entitiesToAdd.begin(); it != m_entitiesToAdd.end(); ++it)
	{
		m_entities.push_back(*it);
		PhysicsEntity* physEntity = dynamic_cast<PhysicsEntity*>(*it);
		if (physEntity != nullptr)
		{
			m_physicsEntities.push_back(physEntity);
		}

		else
		{
			StaticEntity* staticEntity = dynamic_cast<StaticEntity*>(*it);
			if (staticEntity != nullptr)
			{
				m_staticEntities.push_back(staticEntity);
			}
		}
	}

	m_entitiesToAdd.clear();

	mp_Window->setView(*(mp_Scene->m_view));
}

void GameManager::FixedUpdate()
{
	std::cout << "FixedUpdate" << std::endl;
	for (auto it1 = m_entities.begin(); it1 != m_entities.end(); ++it1)
	{
		(*it1)->FixedUpdate();
	}

	for (auto it1 = m_physicsEntities.begin(); it1 != m_physicsEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;

		PhysicsEntity* entity = *it1;
		// Physics entities / physics entities
		for (; it2 != m_physicsEntities.end(); ++it2)
		{
			PhysicsEntity* otherEntity = *it2;
			if (entity->IsColliding(otherEntity))
			{
				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);
			}
		}

		if (!entity->m_physicsCollision)
			continue;

		// Physics entities / static entities
		for (auto it3 = m_staticEntities.begin(); it3 != m_staticEntities.end(); ++it3)
		{
			StaticEntity* otherEntity = *it3;
			if (entity->IsColliding(otherEntity))
			{
				entity->Repulse(otherEntity);
				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);
			}
		}
	}
}

void GameManager::Draw()
{
	mp_Window->clear(m_clearColor);
	
	for (Entity* entity : m_entities)
	{
		mp_Window->draw(*entity->GetSprite());
	}
	
	Debug::Get()->Draw(mp_Window);

	mp_Window->display();
}
