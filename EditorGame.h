/*************************************************************************
  Crytek Source File.
  Copyright (C), Crytek Studios, 2001-2004.
 -------------------------------------------------------------------------
  $Id$
  $DateTime$
  Description: Implements the Editor->Game communication interface.
  
 -------------------------------------------------------------------------
  History:
  - 30:8:2004   11:17 : Created by M?rcio Martins

*************************************************************************/
#ifndef __EDITORGAME_H__
#define __EDITORGAME_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include <IGameRef.h>
#include <IEditorGame.h>

struct IGameStartup;
class CEquipmentSystemInterface;

class CEditorGame :
	public IEditorGame
{
public:
	CEditorGame();
    CEditorGame(const char* binariesDir);
	virtual ~CEditorGame();

	virtual bool Init(ISystem *pSystem,IGameToEditorInterface *pGameToEditorInterface);
    virtual int Update(bool haveFocus, unsigned int updateFlags);
	virtual void Shutdown();
	virtual bool SetGameMode(bool bGameMode);
	virtual IEntity * GetPlayer();
	virtual void SetPlayerPosAng(Vec3 pos,Vec3 viewDir);
	virtual void HidePlayer(bool bHide);
	virtual void OnBeforeLevelLoad();
	virtual void OnAfterLevelLoad(const char *levelName, const char *levelFolder);
	virtual void OnCloseLevel();
	virtual bool BuildEntitySerializationList(XmlNodeRef output);
	virtual bool GetAdditionalMinimapData(XmlNodeRef output);

	virtual IFlowSystem * GetIFlowSystem();
	virtual IGameTokenSystem* GetIGameTokenSystem();
	virtual IEquipmentSystemInterface* GetIEquipmentSystemInterface();

	virtual bool SupportsMultiplayerGameRules() { return true; }
	virtual void ToggleMultiplayerGameRules();

	virtual void RegisterTelemetryTimelineRenderers(Telemetry::ITelemetryRepository* pRepository);

	virtual void OnDisplayRenderUpdated( bool displayHelpers );

private:
    void InitMembers(const char* binariesDir);
    void FillSystemInitParams(SSystemInitParams &startupParams, ISystem* system);
	void InitUIEnums(IGameToEditorInterface* pGTE);
	void InitGlobalFileEnums(IGameToEditorInterface* pGTE);
	void InitActionEnums(IGameToEditorInterface* pGTE);
	void InitEntityClassesEnums(IGameToEditorInterface* pGTE);
	void InitLevelTypesEnums(IGameToEditorInterface* pGTE);
	void InitEntityArchetypeEnums(IGameToEditorInterface* pGTE);
	void InitForceFeedbackEnums(IGameToEditorInterface* pGTE);
	void InitActionInputEnums(IGameToEditorInterface* pGTE);
	void InitReadabilityEnums(IGameToEditorInterface* pGTE);
	void InitActionMapsEnums(IGameToEditorInterface* pGTE);
	void InitLedgeTypeEnums(IGameToEditorInterface* pGTE);
	void InitSmartMineTypeEnums(IGameToEditorInterface* pGTE);
	void InitDamageTypeEnums(IGameToEditorInterface *pGTE);
	void InitDialogBuffersEnum(IGameToEditorInterface* pGTE);
	void InitTurretEnum(IGameToEditorInterface* pGTE);
	void InitDoorPanelEnum(IGameToEditorInterface* pGTE);
	void InitModularBehaviorTreeEnum(IGameToEditorInterface* pGTE);

	bool ConfigureNetContext( bool on );
	static void OnChangeEditorMode( ICVar * );
	void EnablePlayer(bool bPlayer);
	static void ResetClient(IConsoleCmdArgs*);
	static const char *GetGameRulesName();
	void ScanBehaviorTrees(const string& folderName, std::vector<string>& behaviorTrees);
	IGameRef			m_pGame;
	IGameStartup	*m_pGameStartup;
	CEquipmentSystemInterface* m_pEquipmentSystemInterface;

	bool          m_bEnabled;
	bool          m_bGameMode;
	bool          m_bPlayer;
	bool          m_bUsingMultiplayerGameRules;

  const char*   m_binariesDir;

	static ICVar  *s_pEditorGameMode;
	static CEditorGame * s_pEditorGame;
};


#endif //__EDITORGAME_H__
