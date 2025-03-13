#include "Entity.h"

#include "Managers/GameManager.h"
#include "Managers.h"
#include "Utils/Utils.h"
#include "Debug.h"
#include "Sprite.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

void Entity::Initialize()
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	
	mTarget.isSet = false;

	OnInitialize();
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	sf::IntRect rect = m_sprite->getTextureRect();
	sf::Vector2f size = sf::Vector2f(rect.width , rect.height);

	x -= size.x * ratioX;
	y -= size.y * ratioY;

	m_sprite->setPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size = sf::Vector2f(m_sprite->getTextureRect().width , m_sprite->getTextureRect().height);
	sf::Vector2f position = m_sprite->getPosition();

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

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	m_sprite->move(translation);

	if (mTarget.isSet) 
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	m_sprite->update();

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