#include "../Actions/PlayerAction.h"
#include "../Graphics/SpriteSheet.h"
#include <iostream>
#define DASH 300
#define BASE_FRICTION 400.0f;
#define JOYSTICK_X sf::Joystick::getAxisPosition(0, sf::Joystick::X)

//--------------------------------------------------------Walking------------------------------------------
void PlayerAction_Walking::OnStart(Player* _player) {
  if (!_player->m_jumping && !_player->m_dash) dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("run");
  sf::Vector2f pos = _player->GetPosition();
  if (_player->m_lastDir.x == -1) {
	  dynamic_cast<SpriteSheet*>(_player->m_sprite)->setScale(-1, 1);
  }
  if (_player->m_lastDir.x == 1) {
	  dynamic_cast<SpriteSheet*>(_player->m_sprite)->setScale(1, 1);
  }
}

void PlayerAction_Walking::OnUpdate(Player* _player)
{
}

void PlayerAction_Walking::OnEnd(Player* _player) {  }

//--------------------------------------------------------jumping-----------------------------------------
void PlayerAction_jumping::OnStart(Player* _player) {
	if (!_player->m_jumping && _player->m_jumpCount <= 1) {
		dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("jump");
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
	if (_player->m_ammo > 0 && _player->m_shootCooldown <= 0) {
		if (!_player->m_jumping && !_player->m_dash) dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("parry");
		_player->Attack();
	}
}

void PlayerAction_Shooting::OnUpdate(Player* _player) {}

void PlayerAction_Shooting::OnEnd(Player* _player) {}

//--------------------------------------------------------Parrying-----------------------------------------
void PlayerAction_Parrying::OnStart(Player* _player) {
	if (_player->m_parryCooldown <= 0) {
		if (!_player->m_jumping && !_player->m_dash) dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("parry");
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
	if (_player->m_dashCooldown <= 0) {
		dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("dash");
		_player->m_friction = 0.0f;
		_player->Dash();
	}
}

void PlayerAction_Dash::OnUpdate(Player* player)
{
}

void PlayerAction_Dash::OnEnd(Player* player) {;
}
//-----------------------------------------------------------------------------------------------------------

void PlayerAction_Falling::OnStart(Player* _player) {
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("fall");
}

void PlayerAction_Falling::OnUpdate(Player* _player) {
	if (_player->m_sideCollider.down) _player->CheckState(_player->State::land);
}

void PlayerAction_Falling::OnEnd(Player* _player) { }

//-----------------------------------------------------------------------------------------------------------

void PlayerAction_Landing::OnStart(Player* _player) {
	dynamic_cast<SpriteSheet*>(_player->m_sprite)->SetAnimation("land");
}

void PlayerAction_Landing::OnUpdate(Player* _player) {
	
}

void PlayerAction_Landing::OnEnd(Player* _player) {}
