#include "Zilean.h"

Zilean::~Zilean()
{
	ZileanMenu->Remove();
}

Zilean::Zilean(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, true, kCollidesWithHeroes | kCollidesWithMinions);
		Q->SetSkillshot(0.25f, 300.f, 0.f, 900.f);
	}
	if (W = nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
	}
	if (E = nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(550.f);
	}
	if (R = nullptr)
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(900.f);
	}

	ZileanMenu = Parent->AddMenu("Zilean");

	//Menu Options
	ComboMenu->AddMenu("Combo");     // if q is ready cast on enemy, if enemy hit by q, and w is ready- w then q on target.

}

void Zilean::Combo()
{

}