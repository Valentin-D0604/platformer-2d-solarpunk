#include "PlayerAction.h"
#include <iostream>
#define DASH 300

//--------------------------------------------------------Walking------------------------------------------
void PlayerAction_Walking::OnStart(Player* player) {
	if (player->m_lastDir.x > 0) { player->m_velocity.x += player->m_acceleration * player->GetDeltaTime(); }
	if (player->m_lastDir.x < 0) { player->m_velocity.x -= player->m_acceleration * player->GetDeltaTime(); }
}

void PlayerAction_Walking::OnUpdate(Player* player)
{

}

void PlayerAction_Walking::OnEnd(Player* player) {}

//--------------------------------------------------------jumping-----------------------------------------
void PlayerAction_jumping::OnStart(Player* player) {
	if (!player->m_jumping) {
		player->Jump();
	}
	return;
}

void PlayerAction_jumping::OnUpdate(Player* player)
{
}

void PlayerAction_jumping::OnEnd(Player* player) {
	/*JPP += 1;
	if (JPP == 3) {
			timejump = 0;
			JPP = 0;
	}*/
}

//--------------------------------------------------------Shooting-----------------------------------------
void PlayerAction_Shooting::OnStart(Player* player) {
	if (player->m_ammo > 0 && player->m_shootCooldown <= 0) {
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

}

void PlayerAction_Idle::OnEnd(Player* player) {}
//------------------------------------------------------------Dash-------------------------------------------
void PlayerAction_Dash::OnStart(Player* player) {
	if (player->m_dashCooldown <= 0) {
		player->Dash();
	}
}

void PlayerAction_Dash::OnUpdate(Player* player)
{

}

void PlayerAction_Dash::OnEnd(Player* player) {}
//-----------------------------------------------------------------------------------------------------------