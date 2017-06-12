#include "BlitzCrank.h"

BlitzCrank::~BlitzCrank() // We dont want our script to stay around
{
	BlitzCrankMenu->Remove();
}

BlitzCrank::BlitzCrank(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		//Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall | kCollidesWithMinions);
		//Q->SetSkillshot(0.25f, 50.f, 1750.f, 925.f);
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

	Drawings->AddMenu("Drawings");
	DrawHookRange = Drawings->CheckBox("Draw Hook Range", true);
	DrawRRange = Drawings->CheckBox("Draw R Range", true);
	OnlyDrawReady = Drawings->CheckBox("Only Draw Ready", true);
	LaneClearMenu->AddMenu("Lane Clear");
	EFarm = LaneClearMenu->CheckBox("Use E", true);
	RFarm = LaneClearMenu->CheckBox("Use R", false);
	Misc->AddMenu("Misc.");
	FleeKey = Misc->AddKey("Flee Key", 72);
	UseWtoFlee = Misc->CheckBox("Use W to Flee", true);
	HookSettings->AddMenu("Hook Settings");
	AutoHook = HookSettings->CheckBox("Use Hook", true);
	HookMode = HookSettings->AddSelection("Hook Chance", 0, { "Very High", "High" });
}

void BlitzCrank::Combo()
{
	ePredictionChance Chance;

	float RDamage; // We're going to assume they level up R every chance they get
	if (GEntityList->Player()->GetLevel() < 11)
		RDamage = 250;
	else if (GEntityList->Player()->GetLevel() < 16)
		RDamage = 375;
	else if (GEntityList->Player()->GetLevel() > 16)
		RDamage = 500;
	if (HookMode->GetInteger() == 0)
		 Chance = kHitChanceVeryHigh;
	else
		 Chance = kHitChanceHigh;


	
	for (auto pEnemy : GPluginSDK->GetEntityList()->GetAllHeros(false, true))
	{
		auto enemy = GTargetSelector->FindTarget(LowestHealthPriority, SpellDamage, Q->Range());
		if (enemy != nullptr)
		{
			float flDistance = enemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
			if (HookMode->GetInteger() == 0)
			{
				if (Q->IsReady() && enemy->IsValidTarget())
				{
					if ((!enemy->HasBuffOfType(BUFF_SpellShield) || !enemy->HasBuffOfType(BUFF_SpellImmunity)) && enemy != nullptr && (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length() <= 900 && (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length() >= 225)
					{
						AdvPredictionOutput PredOut;
						Q->RunPrediction(enemy, false, kCollidesWithMinions, &PredOut);
						if (PredOut.HitChance != kHitChanceCollision && PredOut.HitChance >= Chance) // fuck colliding with retard minions
						{
							Vec3 Futurepos; GPrediction->GetFutureUnitPosition(enemy, 0.2f, true, Futurepos);
							
							if (Q->Range() >= flDistance)
								Q->CastOnPosition(Futurepos);
						}
					}
				}

			}
			if (enemy->HasBuff("rocketgrab2") && E->IsReady())
			{
				if (E->CastOnPlayer())
				{
					GOrbwalking->SetOverrideTarget(enemy);
				}
			}
			if (enemy->GetHealth() < RDamage || GEntityList->Player()->HealthPercent() < 10)
			{
				if (flDistance < 600)
					R->CastOnPlayer();
			}
		}
		
	}
}

void BlitzCrank::Flee()
{
	if (GetAsyncKeyState(FleeKey->GetInteger()) == 0)
		return;

	if (W->IsReady() && !GEntityList->Player()->IsDead() && UseWtoFlee->Enabled())
	{
		W->CastOnPlayer();
	}
	for (auto pEnemy : GPluginSDK->GetEntityList()->GetAllHeros(false, true))
	{
		float flDistance = pEnemy->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
		auto DangerDist = GEntityList->Player()->GetRealAutoAttackRange(GEntityList->Player()) + 100;
		if (flDistance <= DangerDist && !W->IsReady() && E->IsReady())
		{
			E->CastOnUnit(pEnemy);
		}
	}
	
}

void BlitzCrank::LaneClear()
{
	for (auto pCreep : GEntityList->GetAllMinions(false, true, true))
	{
		if (pCreep != nullptr)
		{
			static int NearbyMinions;
			float flDistance = pCreep->ServerPosition().DistanceTo(GEntityList->Player()->GetPosition());
			if (EFarm->Enabled() && flDistance < 100 && E->IsReady() && pCreep->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), pCreep, kSlotQ))
			{
				if (E->CastOnPlayer())
				{
					GOrbwalking->SetOverrideTarget(pCreep);
				}
			}
			if (RFarm->Enabled() && R->IsReady())
			{
				if (flDistance < R->Radius())
					NearbyMinions++;
				if (NearbyMinions > 2)
				{
					R->CastOnPlayer();
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
	if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo)
		BlitzCrank::Combo();
	
	if (GetAsyncKeyState(FleeKey->GetInteger()) == 0)
		BlitzCrank::Flee();

	if (GPluginSDK->GetOrbwalking()->GetOrbwalkingMode() == kModeLaneClear)
		BlitzCrank::LaneClear();
}

void BlitzCrank::OnRender()
{
	if (OnlyDrawReady->Enabled())
	{
		if (DrawHookRange->Enabled() && Q->IsReady())
			GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 255, 255), Q->Radius());
		if (DrawRRange->Enabled() && R->IsReady())
			GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Radius());
	}
	else
	{
		if (DrawHookRange->Enabled())
			GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 255, 255), Q->Radius());
		if (DrawRRange->Enabled())
			GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Radius());
	}
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

