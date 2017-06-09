#include "Yeah.h"

PluginSetup("Yeah AIO");

#pragma region Events
PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* Target)
{
}

PLUGIN_EVENT(void) OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}

PLUGIN_EVENT(void) OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
{

}

// Return an IUnit object here to force the orbwalker to select it for this tick
PLUGIN_EVENT(IUnit*) OnOrbwalkingFindTarget()
{
	return nullptr;
}

PLUGIN_EVENT(void) OnOrbwalkTargetChange(IUnit* OldTarget, IUnit* NewTarget)
{

}

PLUGIN_EVENT(void) OnOrbwalkNonKillableMinion(IUnit* NonKillableMinion)
{

}

PLUGIN_EVENT(void) OnGameUpdate()
{

}

PLUGIN_EVENT(void) OnRender()
{

}

PLUGIN_EVENT(void) OnSpellCast(CastedSpell const& Args)
{

}

PLUGIN_EVENT(void) OnUnitDeath(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnCreateObject(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnDestroyObject(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnDoCast(CastedSpell const& Args)
{
}

PLUGIN_EVENT(void) OnInterruptible(InterruptibleSpell const& Args)
{

}

PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& Args)
{

}

// Called when issuing an order (e.g move, attack, etc.)
// Return false to stop order from executing
PLUGIN_EVENT(bool) OnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)
{
	return true;
}

PLUGIN_EVENT(void) OnBuffAdd(IUnit* Source, void* BuffData)
{

}

PLUGIN_EVENT(void) OnBuffRemove(IUnit* Source, void* BuffData)
{

}

PLUGIN_EVENT(void) OnGameEnd()
{

}

PLUGIN_EVENT(void) OnLevelUp(IUnit* Source, int NewLevel)
{

}

// Only called for local player, before the spell packet is sent
PLUGIN_EVENT(void) OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
}

PLUGIN_EVENT(void) OnDash(UnitDash* Args)
{

}

PLUGIN_EVENT(void) OnD3DPresent(void* Direct3D9DevicePtr)
{

}

PLUGIN_EVENT(void) OnD3DPreReset(void* Direct3D9DevicePtr)
{

}

PLUGIN_EVENT(void) OnD3DPostReset(void* Direct3D9DevicePtr)
{

}

PLUGIN_EVENT(void) OnRenderBehindHUD()
{

}

// Return false to set this message as handled
PLUGIN_EVENT(bool) OnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	return true;
}

PLUGIN_EVENT(void) OnEnterVisible(IUnit* Source)
{

}

PLUGIN_EVENT(void) OnExitVisible(IUnit* Source)
{

}
#pragma endregion

void AddEvents()
{
	GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
	GEventManager->AddEventHandler(kEventOrbwalkOnAttack, OnOrbwalkAttack);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
	GEventManager->AddEventHandler(kEventOrbwalkFindTarget, OnOrbwalkingFindTarget);
	GEventManager->AddEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
	GEventManager->AddEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	GEventManager->AddEventHandler(kEventOnUnitDeath, OnUnitDeath);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->AddEventHandler(kEventOnIssueOrder, OnIssueOrder);
	GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->AddEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->AddEventHandler(kEventOnGameEnd, OnGameEnd);
	GEventManager->AddEventHandler(kEventOnLevelUp, OnLevelUp);
	GEventManager->AddEventHandler(kEventOnPreCast, OnPreCast);
	GEventManager->AddEventHandler(kEventOnDash, OnDash);
	GEventManager->AddEventHandler(kEventOnD3DPresent, OnD3DPresent);
	GEventManager->AddEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
	GEventManager->AddEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
	GEventManager->AddEventHandler(kEventOnRenderBehindHud, OnRenderBehindHUD);
	GEventManager->AddEventHandler(kEventOnWndProc, OnWndProc);
	GEventManager->AddEventHandler(kEventOnEnterVisible, OnEnterVisible);
	GEventManager->AddEventHandler(kEventOnExitVisible, OnExitVisible);
}

void RemoveEvents()
{
	GEventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkOnAttack, OnOrbwalkAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkFindTarget, OnOrbwalkingFindTarget);
	GEventManager->RemoveEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
	GEventManager->RemoveEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnUnitDeath, OnUnitDeath);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnIssueOrder, OnIssueOrder);
	GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->RemoveEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->RemoveEventHandler(kEventOnGameEnd, OnGameEnd);
	GEventManager->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);
	GEventManager->RemoveEventHandler(kEventOnPreCast, OnPreCast);
	GEventManager->RemoveEventHandler(kEventOnDash, OnDash);
	GEventManager->RemoveEventHandler(kEventOnD3DPresent, OnD3DPresent);
	GEventManager->RemoveEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
	GEventManager->RemoveEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
	GEventManager->RemoveEventHandler(kEventOnRenderBehindHud, OnRenderBehindHUD);
	GEventManager->RemoveEventHandler(kEventOnWndProc, OnWndProc);
	GEventManager->RemoveEventHandler(kEventOnEnterVisible, OnEnterVisible);
	GEventManager->RemoveEventHandler(kEventOnExitVisible, OnExitVisible);
}

// Called when plugin is first loaded
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);
	GGame->PrintChat("League of Yeah AIO Loaded!");
	TopLevel = GPluginSDK->AddMenu("Yeah AIO");
	LocalChamp = GEntityList->Player();
	// go through champs we have memes for
	if (strstr(LocalChamp->ChampionName(), "Lee Sin"))
		ChampSelect = new LeeSin(); // TODO


	AddEvents();
}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{
	GGame->PrintChat("League of Yeah AIO Unloaded!");
	RemoveEvents();
}