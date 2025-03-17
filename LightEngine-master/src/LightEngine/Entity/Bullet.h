#pragma once
#include "PhysicsEntity.h"

class Bullet : public PhysicsEntity
{
	bool m_onTheGround;
	sf::Vector2f m_pos;
	sf::Vector2f m_dir;
	Entity* m_caster;
	float m_speed = 500.f;
	float m_changeDirection = 0.f;
public:
	void InitBullet(sf::Vector2f position,sf::Vector2f direction,Entity* caster, bool state);
	void OnInitialize() override;
	void OnUpdate() override;
	void onCollision(Entity* other) override;

	bool IsBulletOnGround();
};


