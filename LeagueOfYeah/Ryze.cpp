#include "Ryze.h"

Ryze::~Ryze()
{
	RyzeMenu->Remove();

}

Ryze::Ryze(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithHeroes | kCollidesWithMinions);
		Q->SetSkillshot(0.f, 0.25f, 0.f, 1000.f);
	}
	if (W = nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(615.f);
	}
	if (E = nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithHeroes | kCollidesWithMinions);
		E->SetOverrideRange(615.f);
	}
	if (R = nullptr)
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, kCollidesWithHeroes | kCollidesWithMinions);
		R->SetOverrideRange(1750.f);
	}

	// Menu Options
	ComboMenu->AddMenu("Combo");
}

	void Ryze::Combo() // If E is ready, E Target - W Target - Q Target - W Target
	{
		for (auto enemy : GPluginSDK->GetEntityList()->GetAllHeros(false, true))
		{
			if (!enemy->IsDead() && enemy != nullptr)
			{
				float flDistance = enemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());  // Find Position Of enemy + Q 
				if (Q->IsReady() && enemy->IsValidTarget() && flDistance < 1000.f)
				{
					AdvPredictionOutput PredOut; // Prediction
					Q->RunPrediction(enemy, false, kCollidesWithMinions, &PredOut);
					if (PredOut.HitChance != kHitChanceCollision && PredOut.HitChance >= kHitChanceHigh) 
					{
						Vec3 Futurepos; GPrediction->GetFutureUnitPosition(enemy, 0.2f, true, Futurepos);

						if (Q->Range() >= flDistance)
							Q->CastOnPosition(Futurepos);
					}
				}
				if (E->IsReady() && flDistance <= 615.f)
					E->CastOnTarget(enemy);

				if (W->IsReady() && enemy->HasBuff("Flux"))
					W->CastOnTarget(enemy);

				if (Q->IsReady() && enemy->IsValidTarget() && flDistance < 1000.f)
				{
					AdvPredictionOutput PredOut;
					Q->RunPrediction(enemy, false, kCollidesWithMinions, &PredOut);
					if (PredOut.HitChance != kHitChanceCollision && PredOut.HitChance >= kHitChanceHigh) 
					{
						Vec3 Futurepos; GPrediction->GetFutureUnitPosition(enemy, 0.2f, true, Futurepos);

						if (Q->Range() >= flDistance)
							Q->CastOnPosition(Futurepos);
					}
				}
			}
			



		}
	}

	LaneClear->AddMenu("LaneClear")
		void Ryze::LaneClear() // Find Target Minion, E Target, Wait Out cooldown, If E ready, E Target w Buff "Flux"
	{
		for (auto pCreep : GetEntityList()->GetAllMinions(false, true, true))
		{
			if (pCreep != nullptr)
			{
				float flDistance = pCreep->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
				if (E->IsReady() && flDistance <= 615 && pCreep->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), kSlotE))
				{
					if (E->CastOnPlayer())
					{
						GOrbwalking->SetOverrideTarget(pCreep);
					}
				}
			}
		}
	}
	/*auto IsInRange(Vec2 PositionA, Vec2 PositionB, float Range) -> bool
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
	}*/ // Dont Know if I need this

	void Ryze::OnGameUpdate()
	{
		if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo)
			Ryze::Combo();

		if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeLaneClear)
			Ryze::LaneClear();
	}
	
