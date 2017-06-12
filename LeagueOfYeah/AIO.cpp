#include "AIO.h"

Champion::~Champion()
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

	ParentMenu->Remove();
}
IUnit* Champion::GetHero()
{
	return Hero;
}

IMenu* Champion::GetMenu()
{
	return ParentMenu;
}

void Champion::OnGameUpdate()
{

}

void Champion::OnRender()
{

}

void Champion::OnRealSpellCast(CastedSpell const& Args)
{

}

void Champion::OnSpellCast(CastedSpell const& Args)
{

}
bool Champion::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void Champion::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}

void Champion::BeforeAttack(IUnit* Target)
{

}

void Champion::OnInterruptible(InterruptibleSpell const& Args)
{

}

void Champion::OnGapCloser(GapCloserSpell const& Args)
{

}

void Champion::OnLevelUp(IUnit* Source, int NewLevel)
{

}

void Champion::OnPlayAnimation(IUnit* Source, std::string const Args)
{

}

void Champion::OnExitVisible(IUnit* Source)
{

}

void Champion::OnTeleport(OnTeleportArgs* Args)
{

}