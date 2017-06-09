#include "BlitzCrank.h"

BlitzCrank::~BlitzCrank() // We dont want our script to stay around
{
	BlitzCrankMenu->Remove();
}

BlitzCrank::BlitzCrank(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithHeroes | kCollidesWithMinions);
		Q->SetSkillshot(0.f, 0.f, 1750.f, 925.f);
	}
	if (W = nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
	}
	if (E = nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
	}
	if (R = nullptr)
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, kCollidesWithNothing);
		R->SetOverrideRadius(600);
	}

	BlitzCrankMenu = Parent->AddMenu("BlitzCrank");

	// Menu Options
	ComboMenu->AddMenu("Combo");


	HarassMenu->AddMenu("Harass");

	Drawings->AddMenu("Drawings");
	LaneClearMenu->AddMenu("Lane Clear");
	Misc->AddMenu("Misc.");
	HookSettings->AddMenu("Hook Settings");
	HookMode = HookSettings->AddSelection("Hook Mode", 0, )

}