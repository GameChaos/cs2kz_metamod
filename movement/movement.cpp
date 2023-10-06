#include "movement.h"
#include "playermanager.h"
#include "utils/detours.h"
#include "tier0/memdbgon.h"

void movement::InitDetours()
{
	INIT_DETOUR(GetMaxSpeed);
	INIT_DETOUR(ProcessMovement);
	INIT_DETOUR(PlayerMoveNew);
	INIT_DETOUR(CheckParameters);
	INIT_DETOUR(CanMove);
	INIT_DETOUR(FullWalkMove);
	INIT_DETOUR(MoveInit);
	INIT_DETOUR(CheckWater);
	INIT_DETOUR(CheckVelocity);
	INIT_DETOUR(Duck);
	INIT_DETOUR(LadderMove);
	INIT_DETOUR(CheckJumpButton);
	INIT_DETOUR(OnJump);
	INIT_DETOUR(AirAccelerate);
	INIT_DETOUR(Friction);
	INIT_DETOUR(WalkMove);
	INIT_DETOUR(TryPlayerMove);
	INIT_DETOUR(CategorizePosition);
	INIT_DETOUR(FinishGravity);
	INIT_DETOUR(CheckFalling);
	INIT_DETOUR(PlayerMovePost);
	INIT_DETOUR(PostThink);
}

float FASTCALL movement::Detour_GetMaxSpeed(CCSPlayerPawn *pawn)
{
	return GetMaxSpeed(pawn);
}

void FASTCALL movement::Detour_ProcessMovement(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	ProcessMovement(ms, mv);
	MovementPlayer *player = g_pPlayerManager->ToPlayer(ms);
	player->lastProcessedCurtime = utils::GetServerGlobals()->curtime;
	player->lastProcessedTickcount = utils::GetServerGlobals()->tickcount;
}

bool FASTCALL movement::Detour_PlayerMoveNew(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	return PlayerMoveNew(ms, mv);
}

void FASTCALL movement::Detour_CheckParameters(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	CheckParameters(ms, mv);
}

bool FASTCALL movement::Detour_CanMove(CCSPlayerPawnBase *pawn)
{
	return CanMove(pawn);
}

void FASTCALL movement::Detour_FullWalkMove(CCSPlayer_MovementServices *ms, CMoveData *mv, bool ground)
{
	FullWalkMove(ms, mv, ground);
}

bool FASTCALL movement::Detour_MoveInit(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	return MoveInit(ms, mv);
}

bool FASTCALL movement::Detour_CheckWater(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	return CheckWater(ms, mv);
}

void FASTCALL movement::Detour_CheckVelocity(CCSPlayer_MovementServices *ms, CMoveData *mv, const char *a3)
{
	CheckVelocity(ms, mv, a3);
}

void FASTCALL movement::Detour_Duck(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	Duck(ms, mv);
}

bool FASTCALL movement::Detour_LadderMove(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	return LadderMove(ms, mv);
}

void FASTCALL movement::Detour_CheckJumpButton(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	CheckJumpButton(ms, mv);
}

void FASTCALL movement::Detour_OnJump(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	OnJump(ms, mv);
}

void FASTCALL movement::Detour_AirAccelerate(CCSPlayer_MovementServices *ms, CMoveData *mv, Vector &wishdir, float wishspeed, float accel)
{
	AirAccelerate(ms, mv, wishdir, wishspeed, accel);
}

void FASTCALL movement::Detour_Friction(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	Friction(ms, mv);
}

void FASTCALL movement::Detour_WalkMove(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	WalkMove(ms, mv);
}

void FASTCALL movement::Detour_TryPlayerMove(CCSPlayer_MovementServices *ms, CMoveData *mv, Vector *pFirstDest, trace_t_s2 *pFirstTrace)
{
	TryPlayerMove(ms, mv, pFirstDest, pFirstTrace);
}

void FASTCALL movement::Detour_CategorizePosition(CCSPlayer_MovementServices *ms, CMoveData *mv, bool bStayOnGround)
{
	CategorizePosition(ms, mv, bStayOnGround);
}

void FASTCALL movement::Detour_FinishGravity(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	FinishGravity(ms, mv);
}

void FASTCALL movement::Detour_CheckFalling(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	CheckFalling(ms, mv);
}

void FASTCALL movement::Detour_PlayerMovePost(CCSPlayer_MovementServices *ms, CMoveData *mv)
{
	PlayerMovePost(ms, mv);
}

void FASTCALL movement::Detour_PostThink(CCSPlayerPawnBase *pawn)
{
	PostThink(pawn);
}

CCSPlayerController *MovementPlayer::GetController()
{
	return dynamic_cast<CCSPlayerController *>(g_pEntitySystem->GetBaseEntity(CEntityIndex(this->index)));
}

CCSPlayerPawn *MovementPlayer::GetPawn()
{
	CCSPlayerController *controller = this->GetController();
	if (!controller) return nullptr;
	return dynamic_cast<CCSPlayerPawn *>(controller->m_hPawn.Get());
}

Vector& MovementPlayer::GetOrigin()
{
	return this->GetController()->m_hPawn.Get()->m_pSceneNode->m_vecAbsOrigin; // not actually correct
}

void MovementPlayer::SetOrigin(const Vector& origin)
{

}

Vector& MovementPlayer::GetVelocity()
{
	CCSPlayerController *controller = this->GetController();
	if (!controller) return Vector();
	CBasePlayerPawn *pawn = controller->m_hPawn.Get();
	if (!pawn) return Vector();

	return this->GetController()->m_hPawn.Get()->m_vecAbsVelocity; // not actually correct
}

void MovementPlayer::GetVelocity(const Vector& velocity)
{

}