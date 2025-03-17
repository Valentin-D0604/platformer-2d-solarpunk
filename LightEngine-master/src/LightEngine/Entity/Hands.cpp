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

void Hand::OnInitialize()
{
	m_isVulnerable = false;
	m_isSweeping = false;
	m_isGroundSmashing = false;
	m_isThrowing = false;
}

void Hand::OnUpdate()
{
	if (m_isSweeping)
	{
		// Sweep the terrain
	}
	else if (m_isGroundSmashing)
	{
		// Slam the ground
	}
	else if (m_isThrowing)
	{
		// Throw a rock
	}
	else if (m_isVulnerable)
	{
		// Stunned
	}
	else
	{
		// Idle
	}
}

void Hand::OnCollision(Entity* _collidedWith)
{

}

void Hand::Stun() {
	m_isVulnerable = true;
}

void Hand::PerformSweep() {
	m_isGroundSmashing = true;
}

void Hand::PerformGroundSmash() {
	m_isGroundSmashing = true;
}

void Hand::ThrowRock() {
	m_isThrowing = true;
}

void Hand::RemoveArmor() {
	m_isVulnerable = false;
}

void Hand::SetVulnerable(bool vulnerable) {
	m_isVulnerable = vulnerable;
}