#include "../Entity/Platform.h"
#include "../Scene/TestScene.h"
#include "../Collision/RectangleCollider.h"
#include "../Graphics/SpriteSheet.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Platform::OnInitialize() {

	m_sprite = new Sprite();

	SetTag(TestScene::Tag::platform);
}

void Platform::SetTexture(const char* _spritesheet,const char* _sprite)
{
	SpriteSheet* spriteSheet = new SpriteSheet(dynamic_cast<Entity*>(this), GET_MANAGER(ResourceManager)->GetSpriteSheet(_spritesheet));
	spriteSheet->SetSprite(_sprite);
	spriteSheet->SetPlaying(false);
	m_sprite = spriteSheet;
	sf::Vector2f size = sf::Vector2f(m_sprite->getTexture()->getSize());
	sf::Vector2 pos = GetPosition();
	m_collider = new RectangleCollider({ pos.x, pos.y }, { 200, 200 });
	m_collider->SetGizmo(true);
}
