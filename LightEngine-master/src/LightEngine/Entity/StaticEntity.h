#pragma once
#include "Entity.h"
#include "../Collision//RectangleCollider.h"
#include "SFML/Graphics.hpp"
class StaticEntity : public Entity
{
protected:
	RectangleCollider* m_collider;

	virtual void OnInitialize() {};
	virtual void OnCollision(Entity* _other) {};
	virtual void Move(float _x, float _y) override;

private:
	virtual void FixedUpdate();
	virtual void Update();

	friend class PhysicsEntity;
	friend class GameManager;
};

