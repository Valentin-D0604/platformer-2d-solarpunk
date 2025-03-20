#include "Props.h"
#include "../Entity/Platform.h"
#include "../Scene/TestScene.h"
#include "../Collision/RectangleCollider.h"
#include "../Graphics/SpriteSheet.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"

void Props::OnInitialize()
{

	/*m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));*/

	sf::Vector2f size = sf::Vector2f(m_sprite->getTexture()->getSize());
	sf::Vector2 pos = GetPosition();
	SetTag(TestScene::Tag::platform);
}

void Props::SetTexture(const char* _SpriteSheet, const char* _sprite)
{
	SpriteSheet* spriteSheet = new SpriteSheet(dynamic_cast<Entity*>(this), GET_MANAGER(ResourceManager)->GetSpriteSheet(_SpriteSheet));
	spriteSheet->SetSprite(_sprite);
	m_sprite = spriteSheet;
}
