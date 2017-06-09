#include "LeeSin.h"

LeeSin::~LeeSin() // We dont want our script to stay around
{
	LeeMenu->Remove();
}

LeeSin::LeeSin(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithMinions | kCollidesWithHeroes);
		Q->SetSkillshot(0, 0, 1750, 1100);
	}
}