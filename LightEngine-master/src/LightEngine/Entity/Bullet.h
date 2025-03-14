#pragma once
#include "PhysicsEntity.h"

class Bullet : public PhysicsEntity
{
	bool m_OnTheGround;
	sf::Vector2f m_Pos;
	sf::Vector2f m_Dir;
	Entity* m_Caster;
	float m_Speed = 500.f;
public:
	void InitBullet(sf::Vector2f _position,sf::Vector2f _direction,Entity* _caster, bool _state);
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* _other) override;

	bool IsBulletOnGround();
};


