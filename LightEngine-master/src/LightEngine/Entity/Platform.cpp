#include "../Entity/Platform.h"
#include "../Scene/TestScene.h"
#include "../Collision/RectangleCollider.h"
#include "../Graphics/SpriteSheet.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Platform::OnInitialize() {
	SpriteSheet* spriteSheet = new SpriteSheet(this, "Props1");
	spriteSheet->SetSprite("box");
	m_sprite = spriteSheet;

	/*m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));*/

	sf::Vector2f size = sf::Vector2f(m_sprite->getTexture()->getSize());
	sf::Vector2 pos = GetPosition();
	SetTag(TestScene::Tag::platform);
	m_collider = new RectangleCollider({ pos.x, pos.y}, {204, 192});
	m_collider->SetGizmo(true);
}
