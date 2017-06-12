#include "Shaco.h"
#include "SDK/Vector3.h"


Shaco::~Shaco()
{
	ShacoMenu->Remove();
}

Shaco::Shaco(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		Q->SetOverrideRange(400);
	}
	if (W == nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, kCollidesWithNothing);
		W->SetOverrideRange(425);
		W->SetOverrideRadius(300);
	}
	if (E == nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithYasuoWall);
		E->SetOverrideRange(625);
	}
	if (R == nullptr)																				// idk how to use this in script
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRadius(1125);
	}

	ShacoMenu = Parent->AddMenu("Shaco");

	//Menu Options
	ComboMenu->AddMenu("Combo"); 

	HarassMenu->AddMenu("Harass"); 

	FarmMenu->AddMenu("Farm"); 

	Drawings->AddMenu("Drawings");
	DrawRRange = Drawings->CheckBox("Draw R Range", true);
	DrawQRange = Drawings->CheckBox("Draw Q Range", true);
	DrawERange = Drawings->CheckBox("Draw E Range", true);

	Misc->AddMenu("Misc.");

}

void Shaco::Farm() // might as well just do jungle farm
{

}

void Shaco::Combo()
{
	
}

void Shaco::OnRender()
{
	
}

void Shaco::OnSpellCast(CastedSpell const& Args)
{

}
bool Shaco::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void Shaco::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}