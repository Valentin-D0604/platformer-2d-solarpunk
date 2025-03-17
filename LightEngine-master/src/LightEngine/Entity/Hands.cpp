#include "Hands.h"

#include "../Actions/BossAction.h"
#include "../Conditions/BossCondition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/Sprite.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Hand::Stun()
{
}

void Hand::PerformSweep() {
}

void Hand::PerformGroundSmash() {
}

void Hand::ThrowRock() {
}

void Hand::RemoveArmor() {
}

void Hand::SetVulnerable(bool vulnerable) {
	m_isVulnerable = vulnerable;
}