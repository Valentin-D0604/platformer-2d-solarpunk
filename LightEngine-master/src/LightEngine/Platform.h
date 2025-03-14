#pragma once
#include "Entity/PhysicsEntity.h"

class Platform : public PhysicsEntity {
public:
    void OnInitialize() override;
    void onCollision(Entity* other) override;
	void OnUpdate() override;
};