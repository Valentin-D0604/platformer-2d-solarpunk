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

	SetTag(TestScene::Tag::platform);
	m_Collider = new RectangleCollider({ 100, 500 }, { 100, 100 });
	m_Collider->setGizmo(true);
}
