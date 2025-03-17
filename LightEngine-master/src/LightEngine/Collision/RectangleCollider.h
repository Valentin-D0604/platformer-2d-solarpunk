#pragma once
#include "Collider.h"
class RectangleCollider : public Collider
{
protected:
	sf::Vector2f* m_Vertices;
	float m_Rotation;

public:
	RectangleCollider(sf::Vector2f _position, sf::Vector2f _size, float _rotation = 0);

	virtual sf::Vector2f* const getVertices() const;

	virtual bool isColliding(Collider* _other);

	virtual void rotate(float _angle);
	virtual void setRotation(float _rotation) { m_Rotation = _rotation; }

	virtual sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;

	virtual void setPosition(sf::Vector2f _pos, float _ratioX = 0.5f, float _ratioY = 0.5f);
	virtual void move(sf::Vector2f _delta);
	virtual void update();
};

