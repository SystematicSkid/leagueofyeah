#include "BlitzCrank.h"

BlitzCrank::~BlitzCrank() // We dont want our script to stay around
{
	BlitzCrankMenu->Remove();
}

BlitzCrank::BlitzCrank(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall | kCollidesWithMinions);
		Q->SetSkillshot(0.25f, 50.f, 1750.f, 925.f);
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
	DrawHookRange = Drawings->CheckBox("Draw Hook Range", true);
	DrawRRange = Drawings->CheckBox("Draw R Range", true);
	OnlyDrawReady = Drawings->CheckBox("Only Draw Ready", true);
	LaneClearMenu->AddMenu("Lane Clear");
	Misc->AddMenu("Misc.");
	FleeKey = Misc->AddKey("Flee Key", 72);
	UseWtoFlee = Misc->CheckBox("Use W to Flee", true);
	HookSettings->AddMenu("Hook Settings");
	AutoHook = HookSettings->CheckBox("Use Hook", true);
	HookMode = HookSettings->AddSelection("Hook Mode", 0, { "Safe", "Always" });
}

void BlitzCrank::Combo()
{
	for (auto pEnemy : GPluginSDK->GetEntityList()->GetAllHeros(false, true))
	{
		auto enemy = GTargetSelector->FindTarget(LowestHealthPriority, SpellDamage, Q->Range());
		if (enemy != nullptr)
		{
			if (HookMode->GetInteger() == 0)
			{
				if (Q->IsReady() && enemy->IsValidTarget())
				{
					if ((!enemy->HasBuffOfType(BUFF_SpellShield) || !enemy->HasBuffOfType(BUFF_SpellImmunity)) && enemy != nullptr && (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length() <= 900 && (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length() >= 225)
					{
						AdvPredictionOutput PredOut;
						Q->RunPrediction(enemy, false, kCollidesWithMinions, &PredOut);
						if (PredOut.HitChance != kHitChanceCollision && PredOut.HitChance >= kHitChanceVeryHigh) // fuck colliding with retard minions
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
}


auto IsInRange(Vec2 PositionA, Vec2 PositionB, float Range) -> bool
{
	Vec2 DistanceVector = Vec2(PositionA.x - PositionB.x, PositionA.y - PositionB.y);

	return DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y - Range * Range < 0;
}

auto IsInRange(Vec3 PositionA, Vec3 PositionB, float Range) -> bool
{
	Vec2 DistanceVector = Vec2(PositionA.x - PositionB.x, PositionA.z - PositionB.z);

	return DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y - Range * Range < 0;
}

auto FindBestLineCastPosition(std::vector<Vec3> RangeCheckFroms, float range, float castrange, float radius, bool Minions, bool Heroes, FarmLocation& Output) -> void
{
	FarmLocation result;
	result.HitCount = 0;
	for (Vec3 RangeCheckFrom : RangeCheckFroms)
	{
		std::vector<IUnit*> targets, casttargets;

		if (Minions)
		{
			for (auto Minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (!Minion->IsValidTarget() || Minion->IsWard())
					continue;

				if (IsInRange(RangeCheckFrom, Minion->GetPosition(), range)) targets.push_back(Minion);
				if (IsInRange(RangeCheckFrom, Minion->GetPosition(), castrange)) casttargets.push_back(Minion);
			}
		}

		if (Heroes)
		{
			for (auto Champ : GEntityList->GetAllHeros(false, true))
			{
				if (!Champ->IsValidTarget() || Champ->IsClone())
					continue;

				if (IsInRange(RangeCheckFrom, Champ->GetPosition(), range)) targets.push_back(Champ);
				if (IsInRange(RangeCheckFrom, Champ->GetPosition(), castrange)) casttargets.push_back(Champ);
			}
		}

		for (auto target : casttargets)
		{
			Vec3 endpos = RangeCheckFrom.Extend(target->GetPosition(), range);
			std::vector<IUnit*> UnitsHitHolder;
			int count = 0;
			for (auto i : targets)
			{
				if (Distance(i->GetPosition(), Extend(RangeCheckFrom, endpos, -radius / 2), Extend(endpos, RangeCheckFrom, -radius / 2), true) <= radius / 2 + i->BoundingRadius())
				{
					count++;
					UnitsHitHolder.push_back(i);
				}
			}
			if (count > result.HitCount)
			{
				result.HitCount = count;
				result.CastPosition = endpos;
				result.CastPositionFrom = RangeCheckFrom;
				result.CastOnUnit = target;
				result.UnitsHit = UnitsHitHolder;
			}
		}
	}
	Output = result;
}

void BlitzCrank::OnGameUpdate()
{

}

void BlitzCrank::OnRender()
{

}

void BlitzCrank::OnSpellCast(CastedSpell const& Args)
{

}
bool BlitzCrank::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void BlitzCrank::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}

