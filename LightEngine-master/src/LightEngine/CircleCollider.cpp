#include "CircleCollider.h"
#include "RectangleCollider.h"

CircleCollider::CircleCollider(sf::Vector2f _position, float _radius)
{
}

void CircleCollider::setPosition(sf::Vector2f _position, float _ratioX, float _ratioY)
{
	float size = mRadius * 2;

	_position.x -= size * _ratioX;
	_position.y -= size * _ratioY;

	m_position = _position + m_offset;
}

void CircleCollider::move(sf::Vector2f _direction)
{
	m_position += _direction;
}

sf::Vector2f CircleCollider::getPosition(float _ratioX, float _ratioY) const
{
	float size = mRadius * 2;
	sf::Vector2f position = m_position;

	position.x += size * _ratioX;
	position.y += size * _ratioY;

	return position;
}

bool CircleCollider::isColliding(Collider* _other)
{
	bool colliding = false;
	switch (_other->getShapeTag())
	{
		case ShapeTag::Circle:
		{
			CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
			sf::Vector2f otherPos = otherCast->getGlobalPosition();
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
