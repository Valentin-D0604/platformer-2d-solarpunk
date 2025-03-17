#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "../Graphics/Debug.h"

CircleCollider::CircleCollider(sf::Vector2f _position, float _radius)
{
	m_radius = _radius;
	SetPosition(_position);
	m_shapeTag = ShapeTag::circle;
}
void CircleCollider::SetPosition(sf::Vector2f _position, float _ratioX, float _ratioY)
{
	float size = m_radius * 2;

	_position.x -= size * _ratioX;
	_position.y -= size * _ratioY;

	m_position = _position + m_offset;
}

void CircleCollider::Move(sf::Vector2f _direction)
{
	m_position += _direction;
}

sf::Vector2f CircleCollider::GetPosition(float _ratioX, float _ratioY) const
{
	float size = m_radius * 2;
	sf::Vector2f position = m_position;

	position.x += size * _ratioX;
	position.y += size * _ratioY;

	return position;
}

bool CircleCollider::IsColliding(Collider* _other)
{
	bool colliding = false;
	switch (_other->GetShapeTag())
	{
		case ShapeTag::circle:
		{
			CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
			sf::Vector2f otherPos = otherCast->GetPosition();
			float otherRadius = otherCast->GetRadius();

			colliding = CircleCollision(GetPosition(), GetRadius(), otherPos, otherRadius);
		}
		case ShapeTag::rectangle:
		{
			RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
			sf::Vector2f* const& otherVertices = otherCast->GetVertices();

			colliding = CircleRectangleCollision(GetPosition(), GetRadius(), otherVertices);
		}
	}

	return colliding;
}

void CircleCollider::Update()
{
	if (!m_gizmo)
		return;

	sf::Vector2f position = GetPosition();

	Debug::DrawCircle(position.x, position.y, GetRadius(), sf::Color::Red);
}

sf::Vector2f CircleCollider::GetSize() const
{
	return sf::Vector2f(m_radius, m_radius);
}
