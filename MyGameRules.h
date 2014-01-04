#ifndef MYGAMERULES_H
#define MYGAMERULES_H

#include "GameRules.h"

class CMyGameRules : public CGameRules
{
public:
	CMyGameRules();
	virtual ~CMyGameRules();

	virtual void Release() { delete this; }
	virtual void GetMemoryUsage(ICrySizer *pSizer) const { pSizer->Add(sizeof(*this)); }


	virtual bool OnClientConnect(int channelId, bool isReset);
	virtual void OnClientDisconnect(int channelId, EDisconnectionCause cause, const char *desc, bool keepClient);

	IGameRulesSpawningModule*	GetSpawningModule()						
	{ 
		return m_spawningModule;
	}

	// IGameObject
	virtual bool Init( IGameObject * pGameObject );
	virtual void PostInit( IGameObject * pGameObject );
	virtual void InitClient(int channelId);
	virtual void PostInitClient(int channelId);
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	virtual void FullSerialize( TSerialize ser );
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags );
	virtual void PostSerialize();
	virtual void SerializeSpawnInfo( TSerialize ser ) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int updateSlot );
	virtual void HandleEvent( const SGameObjectEvent& );
	virtual void ProcessEvent( SEntityEvent& );
	virtual void SetChannelId(uint16 id) {};
	virtual void SetAuthority( bool auth );
	virtual void PostUpdate( float frameTime );
	virtual void PostRemoteSpawn() {};
	//


protected:

};

#endif