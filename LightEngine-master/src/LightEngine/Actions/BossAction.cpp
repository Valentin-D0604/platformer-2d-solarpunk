#include "BossAction.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"

// ----------------------------------------- BALAYAGE DU TERRAIN -------------------------
void BossAction_Sweeping::OnStart(Boss* _owner) {
    // The boss hands start sweeping the terrain, setting an animation or state if needed
	_owner->m_left->SetVulnerable(true);
	_owner->m_right->SetVulnerable(true);
	_owner->m_left->PerformSweep();
	_owner->m_right->PerformSweep();
}

void BossAction_Sweeping::OnUpdate(Boss* _owner) {
    // Moves the boss hands in a sweeping motion from one side to the other
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	
	// If the player is hit by the boss hands, the player takes damage

	if (_owner->m_left->IsColliding(player) || _owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the player parry the boss hands, the hand he parried is stunned and the other one go back to idle

	if (player->IsParry() && _owner->m_left->IsColliding(player)) {
		_owner->m_left->Stun();
		_owner->StartAttack(BossActionType::idle);
	}
	else if (player->IsParry() && _owner->m_right->IsColliding(player)) {
		_owner->m_right->Stun();
		_owner->StartAttack(BossActionType::idle);
	}

	// If the boss hands have finished sweeping, the boss goes back to idle

	if (_owner->m_left->IsSweeping() == false && _owner->m_right->IsSweeping() == false) {
		_owner->StartAttack(BossActionType::idle);
	}
}

void BossAction_Sweeping::OnEnd(Boss* _owner) {
	// The boss hands stop sweeping the terrain
	_owner->m_left->SetVulnerable(false);
	_owner->m_right->SetVulnerable(false);
}

// ----------------------------------------- FRAPPE AU SOL -------------------------
void BossAction_GroundSmash::OnStart(Boss* _owner) {
    // The boss hands prepare for the ground smash
	_owner->m_left->SetVulnerable(true);
	_owner->m_right->SetVulnerable(true);
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
		_owner->m_left->Stun();
		_owner->StartAttack(BossActionType::idle);
	}
	
	else if (player->IsParry() && _owner->m_right->IsColliding(player)) {
		_owner->m_right->Stun();
		_owner->StartAttack(BossActionType::idle);
	}

	// If the boss hands have finished slamming the ground, the boss goes back to idle

	if (_owner->m_left->IsGroundSmashing() == false && _owner->m_right->IsGroundSmashing() == false) {
		_owner->StartAttack(BossActionType::idle);
	}
}

void BossAction_GroundSmash::OnEnd(Boss* _owner) {
	// The boss hands stop the ground smash and go back to idle
	_owner->m_left->SetVulnerable(false);
	_owner->m_right->SetVulnerable(false);
}

// ----------------------------------------- LANCEMENT DE PROJECTILES -------------------------
void BossAction_Throwing::OnStart(Boss* _owner) {
	// one of the boss hand prepare to throw a projectile at the player
	_owner->m_left->SetVulnerable(true);
	_owner->m_right->SetVulnerable(true);
	_owner->m_left->ThrowRock();

}

void BossAction_Throwing::OnUpdate(Boss* _owner) {
    TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
    Player* player = scene->GetPlayer();

	// If the player is hit by the boss hands, the player takes damage
	if (_owner->m_left->IsColliding(player) || _owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the boss hands throw a projectile, but the player parry it, the projectile go hit the boss and stunns him
	if (player->IsParry() && _owner->m_left->IsThrowing() && _owner->m_left->IsColliding(player)) {
		_owner->Stun();
	}

	// If the boss hands have finished throwing the projectile, the boss goes back to idle

	if (_owner->m_left->IsThrowing() == false && _owner->m_right->IsThrowing() == false) {
		_owner->StartAttack(BossActionType::idle);
	}

}

void BossAction_Throwing::OnEnd(Boss* _owner) {
	// The boss hands stop throwing the projectile
	_owner->m_left->SetVulnerable(false);
	_owner->m_right->SetVulnerable(false);
}

// ----------------------------------------- STUN STATE -------------------------
void BossAction_Stunned::OnStart(Boss* _owner) {
	// The boss is stunned, setting an animation or state if needed
	_owner->m_isStunned = true;
}

void BossAction_Stunned::OnUpdate(Boss* _owner) {
	// The boss is stunned, waiting for the stun to end
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();

	// If the player is hit by the boss hands, the player takes damage
	if (_owner->m_left->IsColliding(player) || _owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the player parry the boss hands, the hand he parried is stunned and the other one go back to idle
	if (player->IsParry() && _owner->m_left->IsColliding(player)) {
		_owner->m_left->Stun();
		_owner->StartAttack(BossActionType::idle);
	}
	else if (player->IsParry() && _owner->m_right->IsColliding(player)) {
		_owner->m_right->Stun();
		_owner->StartAttack(BossActionType::idle);
	}

	// If the boss hands have finished being stunned, the boss goes back to idle

	if (_owner->m_left->IsVulnerable() == false && _owner->m_right->IsVulnerable() == false) {
		_owner->StartAttack(BossActionType::idle);
	}
}

void BossAction_Stunned::OnEnd(Boss* _owner) {
	// The boss is no longer stunned
	_owner->m_isStunned = false;
}

// ----------------------------------------- IDLE -------------------------
void BossAction_Idle::OnStart(Boss* _owner) {}

void BossAction_Idle::OnUpdate(Boss* _owner) {}

void BossAction_Idle::OnEnd(Boss* _owner) {}
