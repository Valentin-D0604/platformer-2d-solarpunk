#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
protected:
	float mRadius;
	sf::Vector2f m_position;

public:
	CircleCollider(sf::Vector2f _position, float _radius);

	virtual void setPosition(sf::Vector2f _position, float _ratioX = 0.5f, float _ratioY = 0.5f);
	virtual void move(sf::Vector2f _direction);
	virtual sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;

	virtual bool isColliding(Collider* _other);

	virtual float getRadius() const { return mRadius; };
	void setRadius(float _radius) { mRadius = _radius; };
	void update();
};

