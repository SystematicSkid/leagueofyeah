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

void AIO::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}

void AIO::OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
{

}

// Return an IUnit object here to force the orbwalker to select it for this tick
IUnit* OnOrbwalkingFindTarget()
{
	return nullptr;
}

void AIO::OnOrbwalkTargetChange(IUnit* OldTarget, IUnit* NewTarget)
{

}

void AIO::OnOrbwalkNonKillableMinion(IUnit* NonKillableMinion)
{

}

void AIO::OnGameUpdate()
{

}

void AIO::OnRender()
{

}

void AIO::OnSpellCast(CastedSpell const& Args)
{

}

void AIO::OnUnitDeath(IUnit* Source)
{

}

void AIO::OnCreateObject(IUnit* Source)
{

}

void AIO::OnDestroyObject(IUnit* Source)
{

}

void AIO::OnDoCast(CastedSpell const& Args)
{
}

void AIO::OnInterruptible(InterruptibleSpell const& Args)
{

}

void AIO::OnGapCloser(GapCloserSpell const& Args)
{

}

// Called when issuing an order (e.g move, attack, etc.)
// Return false to stop order from executing
bool AIO::OnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)
{
	return true;
}

void AIO::OnBuffAdd(IUnit* Source, void* BuffData)
{

}

void AIO::OnBuffRemove(IUnit* Source, void* BuffData)
{

}

void AIO::OnGameEnd()
{

}

void AIO::OnLevelUp(IUnit* Source, int NewLevel)
{

}

// Only called for local player, before the spell packet is sent
void AIO::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
}

void AIO::OnDash(UnitDash* Args)
{

}

void AIO::OnD3DPresent(void* Direct3D9DevicePtr)
{

}

void AIO::OnD3DPreReset(void* Direct3D9DevicePtr)
{

}

void AIO::OnD3DPostReset(void* Direct3D9DevicePtr)
{

}

void AIO::OnRenderBehindHUD()
{

}

// Return false to set this message as handled
bool AIO::OnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	return true;
}

void AIO::OnEnterVisible(IUnit* Source)
{

}

void AIO::OnExitVisible(IUnit* Source)
{

}