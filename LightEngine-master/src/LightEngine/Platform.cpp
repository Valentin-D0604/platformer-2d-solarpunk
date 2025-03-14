#include "Platform.h"
#include "TestScene.h"
#include "RectangleCollider.h"
#include <iostream>

void Platform::OnInitialize() {
    setMass(0);
    setGravityForce(0);
    setGravityDirection({ 0, 0 });
	SetTag(TestScene::Tag::OBJECT);
	m_collider = new RectangleCollider(GetPosition(), { 100, 100 });
}

void Platform::onCollision(Entity* other) {
	
	if (other->IsTag(TestScene::Tag::PLAYER))
	{
		std::cout << "collide with the player";
	}
}

void Platform::OnUpdate() {
}