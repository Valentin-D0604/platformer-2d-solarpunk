#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
protected:
	float m_radius;
	sf::Vector2f m_position;

public:
	CircleCollider(sf::Vector2f _position, float _radius);

	virtual void SetPosition(sf::Vector2f _position, float _ratioX = 0.5f, float _ratioY = 0.5f);
	virtual void Move(sf::Vector2f _direction);
	virtual sf::Vector2f GetPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;

	virtual bool IsColliding(Collider* _other);

	virtual float GetRadius() const { return m_radius; };
	void SetRadius(float _radius) { m_radius = _radius; };
	virtual void Update();

	// Hérité via Collider
	sf::Vector2f GetSize() const override;
};

