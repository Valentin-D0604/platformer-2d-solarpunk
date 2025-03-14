#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "../Graphics/Debug.h"

CircleCollider::CircleCollider(sf::Vector2f _position, float _radius)
{
	m_Radius = _radius;
	setPosition(_position);
	m_shapeTag = ShapeTag::Circle;
}
void CircleCollider::setPosition(sf::Vector2f _position, float _ratioX, float _ratioY)
{
	float size = m_Radius * 2;

	_position.x -= size * _ratioX;
	_position.y -= size * _ratioY;

	m_Position = _position + m_offset;
}

void CircleCollider::move(sf::Vector2f _direction)
{
	m_Position += _direction;
}

sf::Vector2f CircleCollider::getPosition(float _ratioX, float _ratioY) const
{
	float size = m_Radius * 2;
	sf::Vector2f position = m_Position;

	position.x += size * _ratioX;
	position.y += size * _ratioY;

	return position;
}

bool CircleCollider::IsColliding(Collider* _other)
{
	bool colliding = false;
	switch (_other->getShapeTag())
	{
		case ShapeTag::Circle:
		{
			CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
			sf::Vector2f otherPos = otherCast->getPosition();
			float otherRadius = otherCast->getRadius();

			colliding = circleCollision(getPosition(), getRadius(), otherPos, otherRadius);
		}
		case ShapeTag::Rectangle:
		{
			RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
			sf::Vector2f* const& otherVertices = otherCast->getVertices();

			colliding = circleRectangleCollision(getPosition(), getRadius(), otherVertices);
		}
	}

	return colliding;
}

void CircleCollider::update()
{
	if (!m_gizmo)
		return;

	sf::Vector2f position = getPosition();

	Debug::DrawCircle(position.x, position.y, getRadius(), sf::Color::Red);
}

sf::Vector2f CircleCollider::getSize() const
{
	return sf::Vector2f(m_Radius, m_Radius);
}
