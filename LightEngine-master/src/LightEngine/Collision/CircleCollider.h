#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
protected:
	float m_Radius;
	sf::Vector2f m_Position;

public:
	CircleCollider(sf::Vector2f _position, float _radius);

	virtual void setPosition(sf::Vector2f _position, float _ratioX = 0.5f, float _ratioY = 0.5f);
	virtual void move(sf::Vector2f _direction);
	virtual sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;

	virtual bool isColliding(Collider* _other);

	virtual float getRadius() const { return m_Radius; };
	void setRadius(float _radius) { m_Radius = _radius; };
	virtual void update();
};

