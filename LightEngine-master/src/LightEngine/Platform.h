#pragma once
#include "PhysicsEntity.h"

class Platform : public PhysicsEntity {
public:
    void OnInitialize() override;
    void onCollision(sf::CircleShape& player, const sf::RectangleShape& plat);
	void OnUpdate() override;
};