#include "StdAfx.h"
#include "TestActor.h"

CTestActor::CTestActor()
{
}

CTestActor::~CTestActor()
{
	gEnv->pGame->GetIGameFramework()->GetIActorSystem()->RemoveActor(GetEntity()->GetId());
}


bool CTestActor::Init( IGameObject * pGameObject )
{
	SetGameObject(pGameObject);
	gEnv->pGame->GetIGameFramework()->GetIActorSystem()->AddActor(GetEntityId(), this);
	GetEntity()->LoadGeometry(0, "Objects/default/primitive_sphere.cgf");

	SEntityPhysicalizeParams params;
	params.mass = 50.0f;
	params.type = PE_RIGID;
	GetEntity()->Physicalize(params);
	return true;
}

void CTestActor::Reset(bool bToGame)
{

}

void CTestActor::PostInit( IGameObject * pGameObject )
{
}

void CTestActor::InitClient(int channelId)
{
}

void CTestActor::PostInitClient(int channelId)
{
}

bool CTestActor::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	return true;
}

void CTestActor::PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
}

bool CTestActor::GetEntityPoolSignature( TSerialize signature )
{
	return true;
}

void CTestActor::Release()
{
	delete this;
}

void CTestActor::FullSerialize( TSerialize ser )
{
}

bool CTestActor::NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags )
{
	return true;
}

void CTestActor::PostSerialize()
{
}

void CTestActor::SerializeSpawnInfo( TSerialize ser )
{
}


ISerializableInfoPtr CTestActor::GetSpawnInfo()
{
	return 0;
}

void CTestActor::Update( SEntityUpdateContext& ctx, int updateSlot )
{
}

void CTestActor::HandleEvent( const SGameObjectEvent& event )
{
}

void CTestActor::ProcessEvent( SEntityEvent& event )
{
}
	
void CTestActor::SetAuthority( bool auth )
{
}

const void * CTestActor::GetRMIBase() const
{
	return 0;
}

void CTestActor::PostUpdate( float frameTime )
{
}

void CTestActor::PostRemoteSpawn()
{
}

// IActor


void	CTestActor::SetHealth( float health )
{
}

float	CTestActor::GetHealth() const
{
	return 0;
}

int		CTestActor::GetHealthAsRoundedPercentage() const
{
	return 0;
}

void	CTestActor::SetMaxHealth( float maxHealth )
{
}

float	CTestActor::GetMaxHealth() const
{
	return 0.0f;
}

int		CTestActor::GetArmor() const
{
	return 0;
}

int		CTestActor::GetMaxArmor() const
{
	return 0;
}


bool	CTestActor::IsFallen() const
{
	return 0;
}

bool	CTestActor::IsDead() const
{
	return 0;
}

int		CTestActor::IsGod()
{
	return 0;
}

void	CTestActor::Fall(Vec3 hitPos)
{
}

bool	CTestActor::AllowLandingBob()
{
	return false;
}


void	CTestActor::PlayAction(const char *action,const char *extension, bool looping)
{
}

IAnimationGraphState * CTestActor::GetAnimationGraphState()
{
	return 0;
}

void	CTestActor::ResetAnimationState()
{
}


void CTestActor::CreateScriptEvent(const char *event,float value,const char *str)
{
}

bool CTestActor::BecomeAggressiveToAgent(EntityId entityID)
{
	return false;
}


void CTestActor::SetFacialAlertnessLevel(int alertness)
{
}

void CTestActor::RequestFacialExpression(const char* pExpressionName, f32* sequenceLength)
{
}

void CTestActor::PrecacheFacialExpression(const char* pExpressionName)
{
}


EntityId	CTestActor::GetGrabbedEntityId() const
{
	return 0;
}


void CTestActor::HideAllAttachments(bool isHiding)
{
}


void CTestActor::SetIKPos(const char *pLimbName, const Vec3& goalPos, int priority)
{
}


void CTestActor::SetViewInVehicle(Quat viewRotation)
{
}

void CTestActor::SetViewRotation( const Quat &rotation )
{
}

Quat CTestActor::GetViewRotation() const
{
	return Quat::CreateIdentity();
}


bool CTestActor::IsFriendlyEntity(EntityId entityId, bool bUsingAIIgnorePlayer) const
{
	return false;
}

	
Vec3 CTestActor::GetLocalEyePos() const
{
	return Vec3(0,0,0);
}


void CTestActor::CameraShake(float angle,float shift,float duration,float frequency,Vec3 pos,int ID,const char* source)
{
}


IItem* CTestActor::GetHolsteredItem() const
{
	return 0;
}

void CTestActor::HolsterItem(bool holster, bool playSelect, float selectSpeedBias, bool hideLeftHandObject)
{
}

	
IItem* CTestActor::GetCurrentItem(bool includeVehicle) const
{
	return 0;
}

bool CTestActor::DropItem(EntityId itemId, float impulseScale, bool selectNext, bool byDeath)
{
	return false;
}

IInventory *CTestActor::GetInventory() const
{
	return 0;
}

void CTestActor::NotifyCurrentItemChanged(IItem* newItem)
{
}


IMovementController * CTestActor::GetMovementController() const
{
	return 0;
}


	
IEntity *CTestActor::LinkToVehicle(EntityId vehicleId)
{
	return 0;
}


IEntity* CTestActor::GetLinkedEntity() const
{
	return 0;
}


uint8 CTestActor::GetSpectatorMode() const
{
	return 0;
}


bool CTestActor::IsThirdPerson() const
{
	return false;
}

void CTestActor::ToggleThirdPerson()
{
}


bool CTestActor::IsPlayer() const
{
	return GetChannelId() != 0;
}

bool CTestActor::IsClient() const
{
	return false;
}

bool CTestActor::IsMigrating() const
{
	return false;
}

void CTestActor::SetMigrating(bool isMigrating)
{
}


void CTestActor::InitLocalPlayer()
{
}


const char* CTestActor::GetActorClassName() const
{
	return "CTestActor";
}

ActorClass CTestActor::GetActorClass() const
{
	return 0;
}


const char* CTestActor::GetEntityClassName() const
{
	return GetEntity()->GetClass()->GetName();
}


void	CTestActor::SerializeXML( XmlNodeRef& node, bool bLoading )
{
}

void  CTestActor::SerializeLevelToLevel( TSerialize &ser )
{
}


IAnimatedCharacter * CTestActor::GetAnimatedCharacter()
{
	return 0;
}

const IAnimatedCharacter * CTestActor::GetAnimatedCharacter() const
{
	return 0;
}

void CTestActor::PlayExactPositioningAnimation( const char* sAnimationName, bool bSignal, const Vec3& vPosition, const Vec3& vDirection, float startWidth, float startArcAngle, float directionTolerance )
{
}

void CTestActor::CancelExactPositioningAnimation()
{
}

void CTestActor::PlayAnimation( const char* sAnimationName, bool bSignal )
{
}

	
	
void CTestActor::EnableTimeDemo( bool bTimeDemo )
{
}



void CTestActor::SwitchDemoModeSpectator(bool activate)
{
}


	
IVehicle *CTestActor::GetLinkedVehicle() const
{
	return 0;
}


void CTestActor::OnAIProxyEnabled(bool enabled)
{
}

void CTestActor::OnReturnedToPool()
{
}

void CTestActor::OnPreparedFromPool()
{
}

bool CTestActor::ShouldMuteWeaponSoundStimulus() const
{
	return false;
}
