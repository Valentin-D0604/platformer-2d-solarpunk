#pragma once
#include "../Entity/PhysicsEntity.h"

class Collectable : public PhysicsEntity
{
		sf::Vector2f m_pos;
		sf::Vector2f m_dir;
		Entity* m_caster;
		float m_speed = 500.f;
		float m_lifeTime = 5.f;
	public:
		void InitCollec(sf::Vector2f position, sf::Vector2f direction, Entity* caster);
		void OnInitialize() override;
		void OnUpdate() override;
		void OnCollision(Entity* other) override;
};

