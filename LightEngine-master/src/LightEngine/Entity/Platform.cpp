#include "../Entity/Platform.h"
#include "../Scene/TestScene.h"
#include "../Collision/RectangleCollider.h"
#include "../Graphics/Sprite.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Platform::OnInitialize() {
	m_Sprite = new Sprite();
	m_Sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));
	sf::Vector2f size = sf::Vector2f(m_Sprite->getTexture()->getSize());
	sf::Vector2 pos = GetPosition();
	SetTag(TestScene::Tag::platform);
	m_Collider = new RectangleCollider({ pos.x, pos.y}, {200, 200});
	m_Collider->setGizmo(true);
}
