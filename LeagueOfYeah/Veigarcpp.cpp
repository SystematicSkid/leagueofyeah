#include "Veigar.h"
#include "SDK/Vector3.h"


Veigar::~Veigar()
{
	VeigarMenu->Remove();
}

Veigar::Veigar(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithHeroes | kCollidesWithMinions | kCollidesWithYasuoWall);
		Q->SetSkillshot(0.25f, 0.f, 2000.f, 950.f);
	}
	if (W == nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithNothing);
		W->SetOverrideRange(900.f);
		W->SetOverrideRadius(112.5f);
	}
	if (E == nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, kCollidesWithNothing);
		E->SetOverrideRange(650.f);
		E->SetOverrideRadius(375.f);
	}
	if (R == nullptr)
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, false, kCollidesWithYasuoWall);
		R->SetOverrideRange(650.f);
	}
	VeigarMenu = Parent->AddMenu("Veigar");

	//Menu Options
	ComboMenu->AddMenu("Combo"); // Want to Place E so that they walk into it and get stunned, predict where they go so that i Hit W, Then cast Q, then if hp less than R Cast R

	HarassMenu->AddMenu("Harass");  // Auto Q auto = thunderlords / E W Q

	FarmMenu->AddMenu("Farm");  // get minion position, if minion near me less than Q dmg cast q ( prioritise multiple minions in line )

	RCastMenu->AddMenu("RCast");   // I Want to, get enemy hp, if less than ( R damage ) cast on target // Done

	Drawings->AddMenu("Drawings");
	DrawRRange = Drawings->CheckBox("Draw R Range", true);
	DrawQRange = Drawings->CheckBox("Draw Q Range", true);
	DrawERange = Drawings->CheckBox("Draw E Range", true);

	Misc->AddMenu("Misc.");

}

void Veigar::RCast()
{
	for (auto pEnemy : GPluginSDK->GetEntityList()->GetAllHeros(false, true))
	{
		if (pEnemy != nullptr)
		{
			float flDistance = pEnemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
			if (R->IsReady() && flDistance <= 650 && pEnemy->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), pEnemy, kSlotR))
			{
				R->CastOnUnit(pEnemy);
			}


		}
	}
}

void Veigar::Farm()
{
	for (auto pCreep : GEntityList->GetAllMinions(false, true, true))
	{
		if (pCreep != nullptr)
		{
			float flDistance = pCreep->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
			if (QFarm->Enabled() && flDistance < 950 && Q->IsReady() && pCreep->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), pCreep, kSlotQ))
			{
				Q->CastOnUnit(pCreep);
			}
		}
	}
}

void Veigar::Combo()
{
	for (auto pEnemy : GEntityList->GetAllHeros(false, true)) //only enemies
	{
		if (pEnemy != nullptr)
		{
			float flDistance = pEnemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
				if (E->IsReady() && flDistance <= 650 && W->IsReady() && Q->IsReady()) // Redo
				{
					E->CastOnUnit(pEnemy);
						W->CastOnUnit(pEnemy);
						E->CastOnUnit(pEnemy);

				}
				if (R->IsReady() && flDistance <= 650 && pEnemy->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), pEnemy, kSlotR))
				{
					R->CastOnUnit(pEnemy);
			}
		}

	}
}

void Veigar::OnRender()
{
	if (OnlyDrawReady->Enabled())
	{
		if (DrawRRange->Enabled() && R->IsReady())
			GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 255, 255), R->Radius());

			if (DrawQRange->Enabled() && Q->IsReady())
				GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Radius());

				if (DrawERange->Enabled() && E->IsReady())
					GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 0), E->Radius());
	}
}

void Veigar::OnGameUpdate()
{

}

void Veigar::OnSpellCast(CastedSpell const& Args)
{

}
bool Veigar::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void Veigar::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}



