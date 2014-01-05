#include "StdAfx.h"
#include "MyGameRules.h"
#include "Game.h"
#include "SmokeManager.h"
#include "ActorManager.h"
#include "ScriptBind_GameRules.h"
#include "UI/HUD/HUDEventDispatcher.h"
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
	SetGameObject(pGameObject);

	if (!GetGameObject()->BindToNetwork())
		return false;

	if (gEnv->bMultiplayer)
	{
		static int GAMERULES__s_round = 1;
		if (g_pGame->GetGameBrowser())
		{
			const char* natString = g_pGame->GetGameBrowser()->GetNatTypeString();
			CryLog( "GameRules::Init natString=%s", natString);
		}
		if (gEnv->bServer)
		{
			CryLog( "GameRules::Init SERVER");
		}
		else
		{
			CryLog( "GameRules::Init CLIENT");
		}
		CryLog( "Round %d", GAMERULES__s_round);
		GAMERULES__s_round++;
	}

	GetGameObject()->EnablePostUpdates(this);

	m_pGameFramework = g_pGame->GetIGameFramework();
	m_pGameplayRecorder = m_pGameFramework->GetIGameplayRecorder();
	m_pSystem = m_pGameFramework->GetISystem();
	m_pActorSystem = m_pGameFramework->GetIActorSystem();
	m_pEntitySystem = gEnv->pEntitySystem;
	m_pScriptSystem = m_pSystem->GetIScriptSystem();
	m_pMaterialManager = gEnv->p3DEngine->GetMaterialManager();
	
	//Register as ViewSystem listener (for cut-scenes, ...)
	m_pGameFramework->GetIGameRulesSystem()->SetCurrentGameRules(this);
	g_pGame->GetGameRulesScriptBind()->AttachTo(this);

	//CGameMechanismManager::GetInstance()->Inform(kGMEvent_GameRulesInit);

	//InitSessionStatistics();

	CTelemetryCollector* pTelemetryCollector = (CTelemetryCollector*)g_pGame->GetITelemetryCollector();
	if (pTelemetryCollector && gEnv->bServer)
	{
		// This needs to come after the session id has been set (which is currently done in InitSessionStatistics)
		// Clients need to wait until the session id has been serialized to them
		pTelemetryCollector->CreateEventStream();
	}


	/*if (!gEnv->IsEditor() && !gEnv->IsDedicated())
	{
		SHUDEvent initGameRules;
		initGameRules.eventType = eHUDEvent_OnInitGameRules;
		CHUDEventDispatcher::CallEvent(initGameRules);
	}*/

	g_pGame->GetIGameFramework()->RegisterListener(this, "gamerules", FRAMEWORKLISTENERPRIORITY_GAME);
	gEnv->pNetwork->AddHostMigrationEventListener(this, "CGameRules", ELPT_PostEngine);

	return true;
}

void CMyGameRules::PostInit( IGameObject * pGameObject )
{
	// CGameRules::PostInit(pGameObject);
}

void CMyGameRules::InitClient(int channelId)
{
	// CGameRules::InitClient(channelId);
}

void CMyGameRules::PostInitClient(int channelId)
{
	// CGameRules::PostInitClient(channelId);
}

bool CMyGameRules::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	return true;// CGameRules::ReloadExtension(pGameObject, params);
}

bool CMyGameRules::GetEntityPoolSignature( TSerialize signature )
{
	return true;// CGameRules::GetEntityPoolSignature(signature);
}

void CMyGameRules::FullSerialize( TSerialize ser )
{
	// CGameRules::FullSerialize(ser);
}

bool CMyGameRules::NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags )
{
	return true;// CGameRules::NetSerialize(ser, aspect, profile, flags);
}

void CMyGameRules::PostSerialize()
{
	// CGameRules::PostSerialize();
}

void CMyGameRules::Update( SEntityUpdateContext& ctx, int updateSlot )
{
	// CGameRules::Update(ctx, updateSlot);
}

void CMyGameRules::HandleEvent( const SGameObjectEvent& ev)
{
	// CGameRules::HandleEvent(ev);
}

void CMyGameRules::ProcessEvent( SEntityEvent& ev)
{
	switch(ev.event)
	{
		//This is called while loading a saved game
	case ENTITY_EVENT_PRE_SERIALIZE:
		{
			g_pGame->PreSerialize();
			break;
		}

	case ENTITY_EVENT_RESET:
		{
			// done here rather than // CGameRules::Restart so that it is called on clients as well as servers
			//		g_pGame->GetGameAISystem()->Reset(false);
			break;
		}
	case ENTITY_EVENT_POST_SERIALIZE:
		{
			break;
		}
	case ENTITY_EVENT_START_GAME:
		{
			g_pGame->GetGameAudio()->Reset();
			//	m_gameStarted = true;
			break;
		}

	case ENTITY_EVENT_ENTER_SCRIPT_STATE:
		{
			break;
		}
	}
}

void CMyGameRules::SetAuthority( bool auth )
{
	// CGameRules::SetAuthority(auth);
}

void CMyGameRules::PostUpdate( float frameTime )
{
	// CGameRules::PostUpdate(frameTime);
}
