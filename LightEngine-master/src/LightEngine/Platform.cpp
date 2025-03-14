#include "Platform.h"
#include "Scene/TestScene.h"
#include "Collision/RectangleCollider.h"
#include "Graphics/Sprite.h"

#include "Graphics/Debug.h"
#include "Managers/Managers.h"
#include <iostream>

void Platform::OnInitialize() {
	m_Sprite = new Sprite();
	m_Sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

    setMass(0);
    setGravityForce(0);
    setGravityDirection({ 0, 0 });
	SetTag(TestScene::Tag::platform);
	m_Collider = new RectangleCollider(GetPosition(), { 100, 100 });
}

void Platform::onCollision(Entity* other) {
	
	if (other->IsTag(TestScene::Tag::player))
	{
		std::cout << "collide with the player";
	}
}

void Platform::OnUpdate() {
}