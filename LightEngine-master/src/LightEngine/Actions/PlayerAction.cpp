#include "../Actions/PlayerAction.h"
#include "../Graphics/SpriteSheet.h"
#include <iostream>
#define DASH 300
#define BASE_FRICTION 400.0f;

//--------------------------------------------------------Walking------------------------------------------
void PlayerAction_Walking::OnStart(Player* _player) {
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("run");
	//if (_player->m_lastDir.x > 0) { _player->m_Velocity.x += _player->m_acceleration * _player->GetDeltaTime(); } TOFIXHERE NO VELOCITY TROU DU CUL
	//if (_player->m_lastDir.x < 0) { _player->m_Velocity.x -= _player->m_acceleration * _player->GetDeltaTime(); }
}

void PlayerAction_Walking::OnUpdate(Player* _player)
{

}

void PlayerAction_Walking::OnEnd(Player* _player) {}

//--------------------------------------------------------jumping-----------------------------------------
void PlayerAction_jumping::OnStart(Player* _player) {
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("jump");
	if (!_player->m_jumping) {
		_player->Jump();
	}
	return;
}

void PlayerAction_jumping::OnUpdate(Player* _player)
{
}

void PlayerAction_jumping::OnEnd(Player* player) {

}

//--------------------------------------------------------Shooting-----------------------------------------
void PlayerAction_Shooting::OnStart(Player* _player) {
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("attack");
	if (_player->m_ammo > 0 && _player->m_shootCooldown <= 0) {
		_player->Attack();
	}
}

void PlayerAction_Shooting::OnUpdate(Player* _player) {}

void PlayerAction_Shooting::OnEnd(Player* _player) {}

//--------------------------------------------------------Parrying-----------------------------------------
void PlayerAction_Parrying::OnStart(Player* _player) {
	std::cout << "a" << std::endl;
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("parry");
	if (_player->m_parryCooldown <= 0) {
		_player->parry();
	}
}

void PlayerAction_Parrying::OnUpdate(Player* _player) {}

void PlayerAction_Parrying::OnEnd(Player* _player) {}

//------------------------------------------------------------idle-------------------------------------------
void PlayerAction_Idle::OnStart(Player* _player) 
{
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("idle");
}

void PlayerAction_Idle::OnUpdate(Player* _player)
{

}

void PlayerAction_Idle::OnEnd(Player* player) {}
//------------------------------------------------------------Dash-------------------------------------------
void PlayerAction_Dash::OnStart(Player* _player) {
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("run");
	if (_player->m_dashCooldown <= 0) {
		_player->m_friction = 0.0f;
		_player->Dash();
	}
}

void PlayerAction_Dash::OnUpdate(Player* player)
{

}

void PlayerAction_Dash::OnEnd(Player* player) {
//_player->m_friction = BASE_FRICTION;
}
//-----------------------------------------------------------------------------------------------------------