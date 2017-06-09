#pragma once
#include "Yeah.h"

class AIO
{
public:
	AIO(IUnit* Champion, IMenu* ChampMenu);
	~AIO(); // De-constructor

	virtual void OnOrbwalkAttack(IUnit* Source, IUnit* Target)

	virtual void  OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)


	// Return an IUnit object here to force the orbwalker to select it for this tick
	virtual void  OnOrbwalkingFindTarget()


	virtual void OnOrbwalkTargetChange(IUnit* OldTarget, IUnit* NewTarget)


	virtual void OnOrbwalkNonKillableMinion(IUnit* NonKillableMinion)

	virtual void OnGameUpdate()

	virtual void OnRender()	

	virtual void OnSpellCast(CastedSpell const& Args)


	virtual void OnUnitDeath(IUnit* Source)


	virtual void OnCreateObject(IUnit* Source)


	virtual void OnDestroyObject(IUnit* Source)


	virtual void  OnDoCast(CastedSpell const& Args)

	virtual void OnInterruptible(InterruptibleSpell const& Args)


	virtual void OnGapCloser(GapCloserSpell const& Args)


	// Called when issuing an order (e.g move, attack, etc.)
	// Return false to stop order from executing
	virtual void OnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)


	virtual void OnBuffAdd(IUnit* Source, void* BuffData)

	virtual void OnBuffRemove(IUnit* Source, void* BuffData)


	virtual void OnGameEnd()


	virtual void OnLevelUp(IUnit* Source, int NewLevel)


	// Only called for local player, before the spell packet is sent
	virtual void OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)

	virtual void OnDash(UnitDash* Args)

	virtual void OnD3DPresent(void* Direct3D9DevicePtr)


	virtual void OnD3DPreReset(void* Direct3D9DevicePtr)


	virtual void OnD3DPostReset(void* Direct3D9DevicePtr)

	virtual void OnRenderBehindHUD()


	// Return false to set this message as handled
	virtual void OnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)


	virtual void OnEnterVisible(IUnit* Source)

	virtual void OnExitVisible(IUnit* Source)

private:
	IUnit* Champion;
	IMenu* ChampionMenu;
	// Spells
	ISpell2* Q;
	ISpell2* W;
	ISpell2* E;
	ISpell2* R;
};