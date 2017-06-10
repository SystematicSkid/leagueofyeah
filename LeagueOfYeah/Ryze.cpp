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
				float flDistance = enemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
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
				if (E->IsReady() && flDistance <= 615.f)
					E->CastOnTarget(enemy);

				if (W->IsReady() && enemy->HasBuff("flux"))
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
	void Ryze::OnGameUpdate()
	{
		if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo)
			Ryze::Combo();
	}

	void Ryze::OnRender()
	{

	}

	void Ryze::OnSpellCast(CastedSpell const& Args)
	{

	}
	bool Ryze::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
	{
		return true;
	}

	void Ryze::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
	{

	}
