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
		Q->SetOverrideDelay(.25f);
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

void Soraka::Combo()
{
	for (auto pChamp : GPluginSDK->GetEntityList()->GetAllHeros(true, true))
	{
		if (Q->IsReady())
		{
			if (pChamp->GetTeam() == GEntityList->Player()->GetTeam()) // Filter only enemy champs
				continue;
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