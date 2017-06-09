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
		Q->SetSkillshot(0.25, 0, 1750, 1100);
	} 
	// W ability
	if (W == nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetSkillshot(0.2, 0, 0, 700);
	}
	// E ability
	if (E == nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, kCollidesWithNothing);
		E->SetSkillshot(0.25f, 350.f, 0.f, 350.f);
	}
	// R ability
	if (R == nullptr)
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25f, 375.f, 1500.f, 375.f);
	}


	/*
	------------------
	 ORBWalker Settings
	 ------------------
	*/
		//combo

		//harass

		//lane clear

		//wardhop


	/*------------
	 Draw Settings
	 -------------
	*/

}