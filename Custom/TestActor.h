#ifndef TESTACTOR_H
#define TESTACTOR_H

#include "IGameObject.h"


class CTestActor : public CGameObjectExtensionHelper<CTestActor, IActor>
{

public:
	CTestActor();
	virtual ~CTestActor();

	virtual bool Init( IGameObject * pGameObject );
	virtual void PostInit( IGameObject * pGameObject );
	virtual void InitClient(int channelId);
	virtual void PostInitClient(int channelId);
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual bool GetEntityPoolSignature( TSerialize signature );
	virtual void Release();
	virtual void FullSerialize( TSerialize ser );
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags );
	virtual NetworkAspectType GetNetSerializeAspects() { return eEA_All; }
	virtual void PostSerialize();
	virtual void SerializeSpawnInfo( TSerialize ser );

	virtual ISerializableInfoPtr GetSpawnInfo();
	virtual void Update( SEntityUpdateContext& ctx, int updateSlot );
	virtual void HandleEvent( const SGameObjectEvent& event );

	virtual void ProcessEvent( SEntityEvent& event );	
	virtual void SetAuthority( bool auth );
	virtual const void * GetRMIBase() const;
	virtual void PostUpdate( float frameTime );
	virtual void PostRemoteSpawn();

	uint16 GetChannelId() const
	{
	return GetGameObject()->GetChannelId();
	}
	void SetChannelId( uint16 id )
	{
	GetGameObject()->SetChannelId( id );
	}

	virtual void GetMemoryUsage(ICrySizer *pSizer) const { pSizer->Add(sizeof(*this)); }

	// IActor
	virtual void	SetHealth( float health );
	virtual float	GetHealth() const;
	virtual int		GetHealthAsRoundedPercentage() const;
	virtual void	SetMaxHealth( float maxHealth );
	virtual float	GetMaxHealth() const;
	virtual int		GetArmor() const;
	virtual int		GetMaxArmor() const;

	virtual bool	IsFallen() const;
	virtual bool	IsDead() const;
	virtual int		IsGod();
	virtual void	Fall(Vec3 hitPos = Vec3(0,0,0));
	virtual bool	AllowLandingBob();

	virtual void	PlayAction(const char *action,const char *extension, bool looping=false);
	virtual IAnimationGraphState * GetAnimationGraphState();
	virtual void	ResetAnimationState();

	virtual void CreateScriptEvent(const char *event,float value,const char *str = NULL);
	virtual bool BecomeAggressiveToAgent(EntityId entityID);

	virtual void SetFacialAlertnessLevel(int alertness);
	virtual void RequestFacialExpression(const char* pExpressionName = NULL, f32* sequenceLength = NULL);
	virtual void PrecacheFacialExpression(const char* pExpressionName);

	virtual EntityId	GetGrabbedEntityId() const;

	virtual void HideAllAttachments(bool isHiding);

	virtual void SetIKPos(const char *pLimbName, const Vec3& goalPos, int priority);

	virtual void SetViewInVehicle(Quat viewRotation);
	virtual void SetViewRotation( const Quat &rotation );
	virtual Quat GetViewRotation() const;

	virtual bool IsFriendlyEntity(EntityId entityId, bool bUsingAIIgnorePlayer = true) const;

	
	virtual Vec3 GetLocalEyePos() const;

	virtual void	CameraShake(float angle,float shift,float duration,float frequency,Vec3 pos,int ID,const char* source="");

	virtual IItem* GetHolsteredItem() const;
	virtual void HolsterItem(bool holster, bool playSelect = true, float selectSpeedBias = 1.0f, bool hideLeftHandObject = true);
	
	virtual IItem* GetCurrentItem(bool includeVehicle=false) const;
	virtual bool DropItem(EntityId itemId, float impulseScale=1.0f, bool selectNext=true, bool byDeath=false);
	virtual IInventory *GetInventory() const;
	virtual void NotifyCurrentItemChanged(IItem* newItem);

	virtual IMovementController * GetMovementController() const;

	
	virtual IEntity *LinkToVehicle(EntityId vehicleId);

	virtual IEntity* GetLinkedEntity() const;

	virtual uint8 GetSpectatorMode() const;

	virtual bool	IsThirdPerson() const;
	virtual void ToggleThirdPerson();

	virtual bool IsStillWaitingOnServerUseResponse() const { return false; }
	virtual void SetStillWaitingOnServerUseResponse(bool waiting) {}

	virtual void SetFlyMode(uint8 flyMode) {};
	virtual uint8 GetFlyMode() const { return 0; };

	virtual bool IsPlayer() const;
	virtual bool IsClient() const;
	virtual bool IsMigrating() const;
	virtual void SetMigrating(bool isMigrating);

	virtual void InitLocalPlayer();

	virtual const char* GetActorClassName() const;
	virtual ActorClass GetActorClass() const;

	virtual const char* GetEntityClassName() const;

	virtual void	SerializeXML( XmlNodeRef& node, bool bLoading );
	virtual void  SerializeLevelToLevel( TSerialize &ser );

	virtual IAnimatedCharacter * GetAnimatedCharacter();
	virtual const IAnimatedCharacter * GetAnimatedCharacter() const;
	virtual void PlayExactPositioningAnimation( const char* sAnimationName, bool bSignal, const Vec3& vPosition, const Vec3& vDirection, float startWidth, float startArcAngle, float directionTolerance );
	virtual void CancelExactPositioningAnimation();
	virtual void PlayAnimation( const char* sAnimationName, bool bSignal );

	
	virtual bool Respawn()
	{
	CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_WARNING, "Use of IActor::Respawn when not implemented!");
	return false;
	}

	
	virtual void ResetToSpawnLocation()
	{
	CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_WARNING, "Use of IActor::ResetToSpawnLocation when not implemented!");
	}

	
	virtual bool CanBreakGlass() const
	{
	return false;
	}

	
	virtual bool MustBreakGlass() const
	{
	return false;
	}

	
	
	virtual void EnableTimeDemo( bool bTimeDemo );

	virtual void SwitchDemoModeSpectator(bool activate);

	
	

	virtual void SetCustomHead(const char* customHead){};

	
	virtual IVehicle *GetLinkedVehicle() const;

	virtual void OnAIProxyEnabled(bool enabled);
	virtual void OnReturnedToPool();
	virtual void OnPreparedFromPool();

	virtual void MountedGunControllerEnabled(bool val) {};
	virtual bool MountedGunControllerEnabled() const { return false; }

	virtual bool ShouldMuteWeaponSoundStimulus() const;

	
	virtual int GetPhysicalSkipEntities(IPhysicalEntity** pSkipList, const int maxSkipSize) const {return 0;}
};

#endif