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
	m_sprite = new Sprite;
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
	sf::IntRect rect = m_sprite->getTextureRect();
	sf::Vector2f size = sf::Vector2f(rect.width , rect.height);

	sf::Vector2f spriteScale = m_sprite->getScale();
	x -= size.x * ratioX * spriteScale.x;
	y -= size.y * ratioY * spriteScale.y;

	m_sprite->setPosition(x, y);

	//#TODO Optimise
	if (m_Target.m_IsSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		m_Target.m_Distance = Utils::GetDistance(position.x, position.y, m_Target.m_Position.x, m_Target.m_Position.y);
		GoToDirection(m_Target.m_Position.x, m_Target.m_Position.y);
		m_Target.m_IsSet = true;
	}
}

void Entity::SetPosition(sf::Vector2f _pos, float _ratioX, float _ratioY)
{
	sf::IntRect rect = m_sprite->getTextureRect();
	sf::Vector2f size = sf::Vector2f(rect.width, rect.height);

	_pos.x -= size.x * _ratioX;
	_pos.y -= size.y * _ratioY;

	m_sprite->setPosition(_pos.x, _pos.y);

	//#TODO Optimise
	if (m_Target.m_IsSet)
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		m_Target.m_Distance = Utils::GetDistance(position.x, position.y, m_Target.m_Position.x, m_Target.m_Position.y);
		GoToDirection(m_Target.m_Position.x, m_Target.m_Position.y);
		m_Target.m_IsSet = true;
	}
}

void Entity::Move(float _x, float _y)
{
	sf::Vector2f position = GetPosition(0, 0) + sf::Vector2f(_x, _y);
	SetPosition(position.x, position.y, 0, 0);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size = sf::Vector2f(m_sprite->getTextureRect().width , m_sprite->getTextureRect().height);
	sf::Vector2f position = m_sprite->getPosition();

	sf::Vector2f spriteScale = m_sprite->getScale();
	position.x += size.x * ratioX * spriteScale.x;
	position.y += size.y * ratioY * spriteScale.y;

	return position;
}

bool Entity::GoToDirection(int _x, int _y, float _speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(_x - position.x, _y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, _speed);

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

void Entity::SetDirection(float _x, float _y, float _speed)
{
	if (_speed > 0)
		m_Speed = _speed;

	m_Direction = sf::Vector2f(_x, _y);
	m_Target.m_IsSet = false;
}

void Entity::Update()
{
	/*float dt = GetDeltaTime();
	float distance = dt * m_Speed;
	sf::Vector2f translation = distance * m_Direction;
	m_sprite->move(translation);*/
	m_sprite->Update();

	OnUpdate();
}

void Entity::FixedUpdate()
{
	float dt = 1.f/60.f;
	float distance = dt * m_Speed;
	sf::Vector2f translation = distance * m_Direction;
	m_sprite->move(translation);
}

Scene* Entity::GetScene() const
{
	return GET_MANAGER(GameManager)->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GET_MANAGER(GameManager)->GetDeltaTime();
}