#include "BossAction.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"

// ----------------------------------------- BALAYAGE DU TERRAIN -------------------------
void BossAction_Sweeping::OnStart(Boss* owner) {
    // The boss hands start sweeping the terrain, setting an animation or state if needed
	owner->m_left->SetVulnerable(true);
	owner->m_right->SetVulnerable(true);
	owner->m_left->PerformSweep();
	owner->m_right->PerformSweep();
}

void BossAction_Sweeping::OnUpdate(Boss* owner) {
    // Moves the boss hands in a sweeping motion from one side to the other
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	
	// If the player is hit by the boss hands, the player takes damage

	if (owner->m_left->IsColliding(player) || owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the player parry the boss hands, the hand he parried is stunned and the other one go back to idle

	if (player->IsParry() && owner->m_left->IsColliding(player)) {
		owner->m_left->Stun();
		owner->StartAttack(BossActionType::IDLE);
	}
	else if (player->IsParry() && owner->m_right->IsColliding(player)) {
		owner->m_right->Stun();
		owner->StartAttack(BossActionType::IDLE);
	}

	// If the boss hands have finished sweeping, the boss goes back to idle

	if (owner->m_left->IsSweeping() == false && owner->m_right->IsSweeping() == false) {
		owner->StartAttack(BossActionType::IDLE);
	}
}

void BossAction_Sweeping::OnEnd(Boss* owner) {
	// The boss hands stop sweeping the terrain
	owner->m_left->SetVulnerable(false);
	owner->m_right->SetVulnerable(false);
}

// ----------------------------------------- FRAPPE AU SOL -------------------------
void BossAction_GroundSmash::OnStart(Boss* owner) {
    // The boss hands prepare for the ground smash
	owner->m_left->SetVulnerable(true);
	owner->m_right->SetVulnerable(true);
	owner->m_left->PerformGroundSmash();
	owner->m_right->PerformGroundSmash();
}

void BossAction_GroundSmash::OnUpdate(Boss* owner) {
    // Hands slam the ground, creating a delay after impact
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	
	// If the player is hit by the boss hands, the player takes damage

	if (owner->m_left->IsColliding(player) || owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the player parry the boss hands, the hand he parried is stunned and the other one go back to idle

	if (player->IsParry() && owner->m_left->IsColliding(player)) {
		owner->m_left->Stun();
		owner->StartAttack(BossActionType::IDLE);
	}
	
	else if (player->IsParry() && owner->m_right->IsColliding(player)) {
		owner->m_right->Stun();
		owner->StartAttack(BossActionType::IDLE);
	}

	// If the boss hands have finished slamming the ground, the boss goes back to idle

	if (owner->m_left->IsGroundSmashing() == false && owner->m_right->IsGroundSmashing() == false) {
		owner->StartAttack(BossActionType::IDLE);
	}
}

void BossAction_GroundSmash::OnEnd(Boss* owner) {
	// The boss hands stop the ground smash and go back to idle
	owner->m_left->SetVulnerable(false);
	owner->m_right->SetVulnerable(false);
}

// ----------------------------------------- LANCEMENT DE PROJECTILES -------------------------
void BossAction_Throwing::OnStart(Boss* owner) {
	// one of the boss hand prepare to throw a projectile at the player
	owner->m_left->SetVulnerable(true);
	owner->m_right->SetVulnerable(true);
	owner->m_left->ThrowRock();

}

void BossAction_Throwing::OnUpdate(Boss* owner) {
    TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
    Player* player = scene->GetPlayer();

	// If the player is hit by the boss hands, the player takes damage
	if (owner->m_left->IsColliding(player) || owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the boss hands throw a projectile, but the player parry it, the projectile go hit the boss and stunns him
	if (player->IsParry() && owner->m_left->IsThrowing() && owner->m_left->IsColliding(player)) {
		owner->Stun();
	}

	// If the boss hands have finished throwing the projectile, the boss goes back to idle

	if (owner->m_left->IsThrowing() == false && owner->m_right->IsThrowing() == false) {
		owner->StartAttack(BossActionType::IDLE);
	}

}

void BossAction_Throwing::OnEnd(Boss* owner) {
	// The boss hands stop throwing the projectile
	owner->m_left->SetVulnerable(false);
	owner->m_right->SetVulnerable(false);
}

// ----------------------------------------- STUN STATE -------------------------
void BossAction_Stunned::OnStart(Boss* owner) {
	// The boss is stunned, setting an animation or state if needed
	owner->m_isStunned = true;
}

void BossAction_Stunned::OnUpdate(Boss* owner) {
	// The boss is stunned, waiting for the stun to end
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();

	// If the player is hit by the boss hands, the player takes damage
	if (owner->m_left->IsColliding(player) || owner->m_right->IsColliding(player)) {
		player->TakeDamage(1);
	}

	// If the player parry the boss hands, the hand he parried is stunned and the other one go back to idle
	if (player->IsParry() && owner->m_left->IsColliding(player)) {
		owner->m_left->Stun();
		owner->StartAttack(BossActionType::IDLE);
	}
	else if (player->IsParry() && owner->m_right->IsColliding(player)) {
		owner->m_right->Stun();
		owner->StartAttack(BossActionType::IDLE);
	}

	// If the boss hands have finished being stunned, the boss goes back to idle

	if (owner->m_left->IsStunned() == false && owner->m_right->IsStunned() == false) {
		owner->StartAttack(BossActionType::IDLE);
	}
}

void BossAction_Stunned::OnEnd(Boss* owner) {
	// The boss is no longer stunned
	owner->m_isStunned = false;
}

// ----------------------------------------- IDLE -------------------------
void BossAction_Idle::OnStart(Boss* owner) {}

void BossAction_Idle::OnUpdate(Boss* owner) {}

void BossAction_Idle::OnEnd(Boss* owner) {}
