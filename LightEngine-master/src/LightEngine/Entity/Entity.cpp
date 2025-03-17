#include "Entity.h"

#include "../Managers/GameManager.h"
#include "../Managers/Managers.h"
#include "../Utils/Utils.h"
#include "../Graphics/Debug.h"
#include "../Graphics/Sprite.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

void Entity::Initialize()
{
	m_Direction = sf::Vector2f(0.0f, 0.0f);
	
	m_Target.m_IsSet = false;

	OnInitialize();
}

void Entity::Destroy()
{
	m_ToDestroy = true;

	OnDestroy();
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	sf::IntRect rect = m_Sprite->getTextureRect();
	sf::Vector2f size = sf::Vector2f(rect.width , rect.height);

	x -= size.x * ratioX;
	y -= size.y * ratioY;

	m_Sprite->setPosition(x, y);

	//#TODO Optimise
	if (m_Target.m_IsSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		m_Target.m_Distance = Utils::GetDistance(position.x, position.y, m_Target.m_Position.x, m_Target.m_Position.y);
		GoToDirection(m_Target.m_Position.x, m_Target.m_Position.y);
		m_Target.m_IsSet = true;
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size = sf::Vector2f(m_Sprite->getTextureRect().width , m_Sprite->getTextureRect().height);
	sf::Vector2f position = m_Sprite->getPosition();

	position.x += size.x * ratioX;
	position.y += size.y * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	m_Target.m_Position = { x, y };
	m_Target.m_Distance = Utils::GetDistance(position.x, position.y, x, y);
	m_Target.m_IsSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		m_Speed = speed;

	m_Direction = sf::Vector2f(x, y);
	m_Target.m_IsSet = false;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * m_Speed;
	sf::Vector2f translation = distance * m_Direction;
	m_Sprite->move(translation);

	if (m_Target.m_IsSet) 
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + m_Direction.x * m_Target.m_Distance;
		float y2 = y1 + m_Direction.y * m_Target.m_Distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(m_Target.m_Position.x, m_Target.m_Position.y, 5.f, sf::Color::Magenta);

		m_Target.m_Distance -= distance;

		if (m_Target.m_Distance <= 0.f)
		{
			SetPosition(m_Target.m_Position.x, m_Target.m_Position.y, 0.5f, 0.5f);
			m_Direction = sf::Vector2f(0.f, 0.f);
			m_Target.m_IsSet = false;
		}
	}

	m_Sprite->update();

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GET_MANAGER(GameManager)->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GET_MANAGER(GameManager)->GetDeltaTime();
}