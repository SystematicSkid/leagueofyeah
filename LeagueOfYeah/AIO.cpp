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

void AIO::OnGameUpdate()
{

}

void AIO::OnRender()
{

}

void AIO::OnRealSpellCast(CastedSpell const& Args)
{

}

void AIO::OnSpellCast(CastedSpell const& Args)
{

}
bool AIO::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void AIO::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}

void AIO::BeforeAttack(IUnit* Target)
{

}

void AIO::OnInterruptible(InterruptibleSpell const& Args)
{

}

void AIO::OnGapCloser(GapCloserSpell const& Args)
{

}

void AIO::OnLevelUp(IUnit* Source, int NewLevel)
{

}

void AIO::OnPlayAnimation(IUnit* Source, std::string const Args)
{

}

void AIO::OnExitVisible(IUnit* Source)
{

}

void AIO::OnTeleport(OnTeleportArgs* Args)
{

}