#include "BossAction.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Managers/Managers.h"


// ----------------------------------------- IDLE -------------------------
void BossAction_Idle::OnStart(Boss* _owner)
{
	m_idleTimer = 5.0f;
	_owner->m_isIdle = true;
	dynamic_cast<SpriteSheet*>(_owner->m_sprite)->SetAnimation("idle");
}

void BossAction_Idle::OnUpdate(Boss* _owner)
{
	m_idleTimer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (_owner->GetPosition() != _owner->m_position)
	{
		_owner->GoToPosition(_owner->m_position.x, _owner->m_position.y, 0.1f);
	}
	if (m_idleTimer <= 0.0f)
	{
		if (AttackType == 0)
		{
			_owner->CheckState(BossActionType::groundSmash);
			AttackType = 1;
		}
		else
		{
			_owner->CheckState(BossActionType::grabRock);
			AttackType = 0;
		}
	}
}

void BossAction_Idle::OnEnd(Boss* _owner)
{
}

// ----------------------------------------- GroundSmash -------------------------
void BossAction_GroundSmash::OnStart(Boss* _owner)
{
	m_Timer = 4.0f;
	_owner->m_isGroundSmashing = true;
}

void BossAction_GroundSmash::OnUpdate(Boss* _owner) 
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (m_Timer <= 0.0f)
	{
		_owner->StartAttack(BossActionType::idle);
	}
}

void BossAction_GroundSmash::OnEnd(Boss* _owner) 
{

}

// ----------------------------------------- GRAB ROCK -------------------------
void BossAction_GrabRock::OnStart(Boss* _player)
{
	m_Timer = 4.0f;
	_player->m_GrabRock = true;
}

void BossAction_GrabRock::OnUpdate(Boss* _player)
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (m_Timer <= 0.0f)
	{
		_player->StartAttack(BossActionType::throwRock);
	}
}

void BossAction_GrabRock::OnEnd(Boss* _player)
{

}

// ----------------------------------------- LANCEMENT DE PROJECTILES -------------------------
void BossAction_Throwing::OnStart(Boss* _owner) 
{
	m_Timer = 4.0f;
	_owner->m_isThrowing = true;
}

void BossAction_Throwing::OnUpdate(Boss* _owner) 
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (m_Timer <= 0.0f)
	{
		_owner->StartAttack(BossActionType::retreat);
	}
}

void BossAction_Throwing::OnEnd(Boss* _owner) 
{

}
//------------------------------------------RETRAIT --------------------------------
void BossAction_Retreat::OnStart(Boss* _owner)
{
	m_Timer = 4.0f;
	_owner->m_isRetreating = true;
}
void BossAction_Retreat::OnUpdate(Boss* _owner) 
{

	_owner->m_left->GoToPosition(0, 0);
	_owner->m_right->GoToPosition(0, 0);
	if (_owner->m_left->GetPosition().x == 0 && _owner->m_left->GetPosition().y == 0) {
		_owner->StartAttack(BossActionType::idle);
	}

}
void BossAction_Retreat::OnEnd(Boss* _owner)
{

}