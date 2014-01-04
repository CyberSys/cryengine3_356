#include "StdAfx.h"
#include "MyGameRules.h"


CMyGameRules::CMyGameRules() : CGameRules()
{
}

CMyGameRules::~CMyGameRules()
{

}

bool CMyGameRules::OnClientConnect(int channelId, bool isReset)
{
	IScriptTable* pTable = GetEntity()->GetScriptTable();
	const char* playerClass = 0;
	if (pTable)
	{
		IScriptSystem* pScriptSystem = gEnv->pScriptSystem;
		pScriptSystem->BeginCall(pTable, "OnClientConnect");
		pScriptSystem->EndCall();

		pTable->GetValue("PlayerClass", playerClass);
		if (!playerClass)
		{
			playerClass = "TestActor";
			GameWarning("No player class specified, using %s", playerClass);
		}
	}

	IEntity* pSpawner = 0;
	IEntityClass* pSpawnerClass = gEnv->pEntitySystem->GetClassRegistry()->FindClass("Fan");
	if (pSpawnerClass)
		if (IEntityIt* pEntItr = gEnv->pEntitySystem->GetEntityIterator())
		{
			IEntity* pEntity = 0;
			while (pEntity = pEntItr->Next())
			{
				if (pEntity->GetClass() == pSpawnerClass)
				{
					pSpawner = pEntity;
					break;
				}
			}
		}

	if (!pSpawner)
		GameWarning("No Spawner Entity to spawn player on");

	IActor* pPlayer = 0;
	Vec3 spawnPos = pSpawner ? pSpawner->GetWorldPos() : Vec3(0,0,0);
	Quat spawnRot = pSpawner ? pSpawner->GetWorldRotation() : Quat::CreateIdentity();

	IActorSystem* pActorSystem = gEnv->pGame->GetIGameFramework()->GetIActorSystem();
	pPlayer = pActorSystem->CreateActor(channelId, "MyPlayer", playerClass, spawnPos, spawnRot, Vec3(1,1,1));

	return pPlayer != 0;
}

void CMyGameRules::OnClientDisconnect(int channelId, EDisconnectionCause cause, const char *desc, bool keepClient)
{
	GameWarning("OnClientDisconnect: %d, %s, keep=%d", channelId, desc, (int)keepClient);

	IActor* pPlayer = gEnv->pGame->GetIGameFramework()->GetIActorSystem()->GetActorByChannelId(channelId);
	if (pPlayer)
	{
		pPlayer->Release();
	}
}

bool CMyGameRules::Init( IGameObject * pGameObject )
{
	return CGameRules::Init(pGameObject);
}

void CMyGameRules::PostInit( IGameObject * pGameObject )
{
	CGameRules::PostInit(pGameObject);
}

void CMyGameRules::InitClient(int channelId)
{
	CGameRules::InitClient(channelId);
}

void CMyGameRules::PostInitClient(int channelId)
{
	CGameRules::PostInitClient(channelId);
}

bool CMyGameRules::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	return CGameRules::ReloadExtension(pGameObject, params);
}

bool CMyGameRules::GetEntityPoolSignature( TSerialize signature )
{
	return CGameRules::GetEntityPoolSignature(signature);
}

void CMyGameRules::FullSerialize( TSerialize ser )
{
	CGameRules::FullSerialize(ser);
}

bool CMyGameRules::NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags )
{
	return CGameRules::NetSerialize(ser, aspect, profile, flags);
}

void CMyGameRules::PostSerialize()
{
	CGameRules::PostSerialize();
}

void CMyGameRules::Update( SEntityUpdateContext& ctx, int updateSlot )
{
	CGameRules::Update(ctx, updateSlot);
}

void CMyGameRules::HandleEvent( const SGameObjectEvent& ev)
{
	CGameRules::HandleEvent(ev);
}

void CMyGameRules::ProcessEvent( SEntityEvent& ev)
{
	CGameRules::ProcessEvent(ev);
}

void CMyGameRules::SetAuthority( bool auth )
{
	CGameRules::SetAuthority(auth);
}

void CMyGameRules::PostUpdate( float frameTime )
{
	CGameRules::PostUpdate(frameTime);
}
