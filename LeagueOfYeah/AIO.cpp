#include "AIO.h"

AIO::~AIO()
{
	// We  want to check if the spells are actually there before we delete the memes
	if (Q)
		delete Q;
	if (W)
		delete W;
	if (E)
		delete E;
	if (R)
		delete R;

	ChampionMenu->Remove();
}

void AIO::OnOrbwalkBeforeAttack(IUnit* Target)
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