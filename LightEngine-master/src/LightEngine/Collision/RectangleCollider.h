#pragma once
#include "Collider.h"


class RectangleCollider : public Collider
{
protected:
	sf::Vector2f* m_vertices;
	float m_rotation;

public:
	RectangleCollider(sf::Vector2f _position, sf::Vector2f _size, float _rotation = 0);

	virtual sf::Vector2f* const GetVertices() const;

	virtual bool IsColliding(Collider* _other);

	virtual void Rotate(float _angle);
	virtual void SetRotation(float _rotation) { m_rotation = _rotation; }

	virtual sf::Vector2f GetPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;
	virtual sf::Vector2f GetSize() const;

	virtual void SetPosition(sf::Vector2f _pos, float _ratioX = 0.5f, float _ratioY = 0.5f);
	virtual void Move(sf::Vector2f _delta);
	virtual void Update();
};

