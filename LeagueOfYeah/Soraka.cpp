#include "Soraka.h"
Soraka::~Soraka()
{
	SorakaMenu->Remove();

}

Soraka::Soraka(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
		Q->SetOverrideDelay(.50f);
		Q->SetOverrideRadius(235.f);
		Q->SetOverrideRange(800.f);
	}
	if (W = nullptr)
	{
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(500);
	}
	if (E = nullptr)
	{
		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, true, kCollidesWithNothing);
		E->SetOverrideRange(925.f);
	}
	if (R = nullptr)
	{
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(FLT_MAX);
	}

	// Menu Options
	SorakaMenu = GPluginSDK->AddMenu("Soraka");
	ComboMenu = SorakaMenu->AddMenu("Combo");
	LaneClearMenu = SorakaMenu->AddMenu("LaneClear");

	KillStealQ = ComboMenu->CheckBox("Killsteal w/ Q", false);
}

std::vector<IUnit*> Soraka::GetHerosNearby(bool friendly, bool enemy, float distance, IUnit* source)
{
	auto minions = GEntityList->GetAllHeros(friendly, enemy);
	auto local = source;

	minions.erase(std::remove_if(minions.begin(), minions.end(), [&](IUnit* m) { return !m || m->IsDead() || !local->IsValidTarget(m, distance); }));

	return minions;
}

void Soraka::Combo()
{
	for (auto pChamp : GPluginSDK->GetEntityList()->GetAllHeros(true, true)) // we use both friendly and enemy because 
	{
		if(pChamp == nullptr)
			continue;

		if (Q->IsReady())
		{
			if (pChamp->GetTeam() == GEntityList->Player()->GetTeam()) // Filter only enemy champs
				continue; // continue means we jump to the next hero in the loop
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (target != nullptr && !target->IsDashing())
			{
				if (!KillStealQ->Enabled() && target->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ))
					return;

				AdvPredictionOutput PredOut;
				Q->RunPrediction(target, true, kCollidesWithNothing, &PredOut);
				if (PredOut.HitChance >= kHitChanceHigh)
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.35f, false, pred);
					Q->CastOnPosition(pred);
				}
				else if (PredOut.HitChance == kHitChanceDashing)
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.35f, false, pred);
					Q->CastOnTarget(target, kHitChanceDashing);
				}
			}
		}
		if (W->IsReady())
		{
			if(pChamp->GetTeam() != GEntityList->Player()->GetTeam()) // Filter only friendly champs
				continue;
			auto ally = GTargetSelector->FindTarget(LowestHealthPriority, TrueDamage, W->Range()); // idk what to put for damage type
			if (ally != nullptr && !ally->IsDashing())
			{
				if(ally->HealthPercent() > 40) // dont heal if health is over 40 percent, we gain salvation passive
					continue;
				if(GUtility->IsPositionInFountain(ally->GetPosition(), true, false)) // we dont want to heal them in fountain, thats just sus lol
					continue;

				W->CastOnUnit(ally); // We good to go and heal this nibba
			}
		}
		if (E->IsReady()) // its basically the same as Q logic, except no delay
		{
			if (pChamp->GetTeam() == GEntityList->Player()->GetTeam()) // Filter only enemy champs
				continue;
		
			auto target = GTargetSelector->FindTarget(LowestHealthPriority, SpellDamage, E->Range());
			if (target != nullptr && !target->IsDashing())
			{

				AdvPredictionOutput PredOut;
				Q->RunPrediction(target, true, kCollidesWithNothing, &PredOut);
				if (PredOut.HitChance >= kHitChanceHigh)
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.35f, false, pred);
					E->CastOnPosition(pred);
				}
				else if (PredOut.HitChance == kHitChanceDashing)
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.35f, false, pred);
					E->CastOnTarget(target, kHitChanceDashing);
				}
			}
		}
		if (R->IsReady())
		{
			

			if (pChamp->GetTeam() != GEntityList->Player()->GetTeam()) // Filter only friendly champs
				continue;
			std::vector<IUnit*> NearbyEnemy = GetHerosNearby(false, true, 500, pChamp);
			std::vector<IUnit*> NearbyAlly = GetHerosNearby(true, false, 500, pChamp);
			if (pChamp->HealthPercent() < 10 && !GUtility->IsPositionInFountain(pChamp->GetPosition(), true, true)) // we'll do some logic in this loop
			{
				if (NearbyEnemy.size() >= 2 && NearbyAlly.size() == 0)
					return;
				if (NearbyEnemy.size() == 0) // dont waste R on jungle if hes low or something lol
					return;
				if (pChamp->HasBuff("UndyingRage"))
					return;
				R->CastOnPlayer();
			}
		}
	}
}


void Soraka::LaneClear() // Find Target Minion, E Target, Wait Out cooldown, If E ready, E Target w Buff "Flux"
{
	
}

void Soraka::OnGameUpdate()
{
	if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo)
		Soraka::Combo();

	if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeLaneClear)
		Soraka::LaneClear();
}

void Soraka::OnRender()
{

}

void Soraka::OnSpellCast(CastedSpell const& Args)
{

}
bool Soraka::OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
	return true;
}

void Soraka::OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}