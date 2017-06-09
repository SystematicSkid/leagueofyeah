#include "LeeSin.h"

LeeSin::~LeeSin() // We dont want our script to stay around
{
	LeeMenu->Remove();
}

LeeSin::LeeSin(IUnit* Lee, IMenu* ChampMenu) :AIO(Lee, ChampMenu)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithMinions | kCollidesWithHeroes);
		Q->SetSkillshot(0, 0, 1750, 1100);
	}
}