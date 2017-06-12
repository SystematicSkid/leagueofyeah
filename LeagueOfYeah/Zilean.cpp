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
	if (W == nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
	}
	if (E == nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(550.f);
	}
	if (R == nullptr)
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
	for (auto pEnemy : GPluginSDK->GetEntityList()->GetAllHeros(false, true))
	{
		auto enemy = GTargetSelector->FindTarget(LowestHealthPriority, SpellDamage, Q->Range());
		if (enemy != nullptr)
		{
			if (Q->IsReady() && enemy->IsValidTarget())
			{
				AdvPredictionOutput PredOut;
				Q->RunPrediction(enemy, true, kCollidesWithMinions, &PredOut);
				if (!enemy->HasBuffOfType(BUFF_SpellShield) || !enemy->HasBuffOfType(BUFF_SpellImmunity))
				{
					if (PredOut.HitChance != kHitChanceCollision && PredOut.HitChance >= kHitChanceHigh)
					{
						Vec3 Futurepos; GPrediction->GetFutureUnitPosition(enemy, 0.2f, true, Futurepos);
						float flDistance = enemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
						if (Q->Range() >= flDistance)
							Q->CastOnPosition(Futurepos);
					}
				}
			}
		}
	}
}

void Zilean::OnGameUpdate()
{

}

void Zilean::OnRender()
{

}

void Zilean::OnSpellCast(CastedSpell const& Args)
{

}
bool Zilean::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void Zilean::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}

