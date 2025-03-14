#include "BossAction.h"
#include "TestScene.h"
#include "Player.h"

// ----------------------------------------- BALAYAGE DU TERRAIN -------------------------
void BossAction_Sweeping::OnStart(Boss* owner) {
    owner->SetVulnerable(true); // The boss is vulnerable during this attack
}

void BossAction_Sweeping::OnUpdate(Boss* owner) {
    owner->MoveSideToSide(400);
}

void BossAction_Sweeping::OnEnd(Boss* owner) {
    owner->SetVulnerable(false); // The boss is no longer vulnerable
}

// ----------------------------------------- FRAPPE AU SOL -------------------------
void BossAction_GroundSmash::OnStart(Boss* owner) {
    // The boss starts preparing for the ground smash
    owner->SetAnimation("ground_smash");
}

void BossAction_GroundSmash::OnUpdate(Boss* owner) {

    owner->PerformGroundSlam();
    owner->SetSpeed(100); // Temporary slow effect
}

void BossAction_GroundSmash::OnEnd(Boss* owner) {
    owner->SetSpeed(200); // Restore normal speed
}

// ----------------------------------------- LANCEMENT DE PROJECTILES -------------------------
void BossAction_Throwing::OnStart(Boss* owner) {
    owner->SetAnimation("throw_projectiles");
    owner->m_shootCooldown = 2.f; // Reset cooldown
}

void BossAction_Throwing::OnUpdate(Boss* owner) {
    TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
    Player* player = scene->GetPlayer();

    owner->m_shootCooldown -= owner->GetDeltaTime();
    if (owner->m_shootCooldown <= 0) {
        owner->ThrowProjectiles(); // Launch projectiles with warning indicators
        owner->m_shootCooldown = 2.f;
    }
}

void BossAction_Throwing::OnEnd(Boss* owner) {
}

// ----------------------------------------- STUN STATE -------------------------
void BossAction_Stunned::OnStart(Boss* owner) {
    owner->SetVulnerable(true);
    owner->RemoveArmor();
    owner->SetAnimation("stunned");
}

void BossAction_Stunned::OnUpdate(Boss* owner) {
    // Stun duration countdown
    owner->m_stunTimer -= owner->GetDeltaTime();
    if (owner->m_stunTimer <= 0) {
        owner->ChangeState(new BossAction_Idle());
    }
}

void BossAction_Stunned::OnEnd(Boss* owner) {
    owner->SetVulnerable(false);
}

// ----------------------------------------- IDLE -------------------------
void BossAction_Idle::OnStart(Boss* owner) {}

void BossAction_Idle::OnUpdate(Boss* owner) {}

void BossAction_Idle::OnEnd(Boss* owner) {}
