#include "PlayerAction.h"

//--------------------------------------------------------Walking------------------------------------------
void PlayerAction_Walking::OnStart(Player* player) {}

void PlayerAction_Walking::OnUpdate(Player* player)
{
	//if (player->m_lastDir.x > 0) { player->m_velocity.x += player->m_acceleration * player->GetDeltaTime(); }
	//if (player->m_lastDir.x < 0) { player->m_velocity.x -= player->m_acceleration * player->GetDeltaTime(); }
}

void PlayerAction_Walking::OnEnd(Player* player) {}

//--------------------------------------------------------jumping-----------------------------------------
void PlayerAction_jumping::OnStart(Player* player) {
	//player->m_OldY = player->GetPosition().y;
	//player->m_jumping = true;
//	player->setGravityForce(-200);
}

void PlayerAction_jumping::OnUpdate(Player* player)
{
	if (player->GetPosition().y >= player->m_OldY && player->m_jumping) {
		player->m_jumping = false;
	}
}

void PlayerAction_jumping::OnEnd(Player* player) {}

//--------------------------------------------------------Shooting-----------------------------------------
void PlayerAction_Shooting::OnStart(Player* player) {
	if (player->m_ammo > 0) {
		player->Attack();
	}
}

void PlayerAction_Shooting::OnUpdate(Player* player) {}

void PlayerAction_Shooting::OnEnd(Player* player) {}

//--------------------------------------------------------Parrying-----------------------------------------
void PlayerAction_Parrying::OnStart(Player* player) {
	if (player->m_parryCooldown <= 0) {
		player->parry();
	}
}

void PlayerAction_Parrying::OnUpdate(Player* player) {}

void PlayerAction_Parrying::OnEnd(Player* player) {}

//------------------------------------------------------------idle-------------------------------------------
void PlayerAction_Idle::OnStart(Player* player) {}

void PlayerAction_Idle::OnUpdate(Player* player)
{
	if (player->m_velocity.x != 0) {
		player->m_velocity.x = 0;
	}
}

void PlayerAction_Idle::OnEnd(Player* player) {}
//-----------------------------------------------------------------------------------------------------------