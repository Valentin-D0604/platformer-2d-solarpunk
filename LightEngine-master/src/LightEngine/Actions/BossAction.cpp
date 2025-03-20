#include "BossAction.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"

// ----------------------------------------- FRAPPE AU SOL -------------------------
void BossAction_GroundSmash::OnStart(Boss* _owner) {
    // The boss hands prepare for the ground smash
	_owner->m_left->PerformGroundSmash();
	_owner->m_right->PerformGroundSmash();
}

void BossAction_GroundSmash::OnUpdate(Boss* _owner) {
    // Hands slam the ground, creating a delay after impact
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	
	// If the player is hit by the boss hands, the player takes damage

	if (_owner->m_left->IsColliding(player) || _owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the player parry the boss hands, the hand he parried is stunned and the other one go back to idle

	if (player->IsParry() && _owner->m_left->IsColliding(player)) {
	}
	
	else if (player->IsParry() && _owner->m_right->IsColliding(player)) {
	}

	// If the boss hands have finished slamming the ground, the boss goes back to idle

	if (_owner->m_left->IsGroundSmashing() == false && _owner->m_right->IsGroundSmashing() == false) {
		_owner->StartAttack(BossActionType::idle);
	}
}

void BossAction_GroundSmash::OnEnd(Boss* _owner) {
	// The boss hands stop the ground smash and go back to idle
}

// ----------------------------------------- LANCEMENT DE PROJECTILES -------------------------
void BossAction_Throwing::OnStart(Boss* _owner) {
	// one of the boss hand prepare to throw a projectile at the player
	_owner->m_left->ThrowRock();

}

void BossAction_Throwing::OnUpdate(Boss* _owner) {
    TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
    Player* player = scene->GetPlayer();

	// If the player is hit by the boss hands, the player takes damage
	if (_owner->m_left->IsColliding(player) || _owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}
	// If the boss hands have finished throwing the projectile, the boss goes back to idle

	if (_owner->m_left->IsThrowing() == false && _owner->m_right->IsThrowing() == false) {
		_owner->StartAttack(BossActionType::idle);
	}

}

void BossAction_Throwing::OnEnd(Boss* _owner) {
	// The boss hands stop throwing the projectile
}
//------------------------------------------RETRAIT --------------------------------
void BossAction_Retreat::OnStart(Boss* _owner) {
	// The boss hands prepare to retreat
	_owner->m_left->Stop();
	_owner->m_right->Stop();
}
void BossAction_Retreat::OnUpdate(Boss* _owner) {
	// The boss hands retreat
	_owner->m_left->GoToPosition(0, 0);
	_owner->m_right->GoToPosition(0, 0);
	// If the boss hands have finished retreating, the boss goes back to idle
	if (_owner->m_left->GetPosition().x == 0 && _owner->m_left->GetPosition().y == 0) {
		_owner->StartAttack(BossActionType::idle);
	}
}
void BossAction_Retreat::OnEnd(Boss* _owner) {
	// The boss hands stop retreating
}
// ----------------------------------------- IDLE -------------------------
void BossAction_Idle::OnStart(Boss* _owner) 
{
	_owner->m_isIdle = true;
}

void BossAction_Idle::OnUpdate(Boss* _owner)
{
	if (_owner->GetPosition() != _owner->m_position)
	{
		_owner->GoToPosition(_owner->m_position.x,_owner->m_position.y,0.1f);
	}
}

void BossAction_Idle::OnEnd(Boss* _owner)
{}

// ----------------------------------------- GRAB ROCK -------------------------
void BossAction_GrabRock::OnStart(Boss* _player)
{
}

void BossAction_GrabRock::OnUpdate(Boss* _player)
{
}

void BossAction_GrabRock::OnEnd(Boss* _player)
{
}
