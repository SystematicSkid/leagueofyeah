#pragma once
#include "AIO.h"
#include "Geom.h"
#include "SDK/Vector3.h"

struct FarmLocation
{
	Vec3 CastPosition;
	Vec3 CastPositionFrom;
	int HitCount = 0;
	IUnit* CastOnUnit = nullptr;
	std::vector<IUnit*> UnitsHit;
};

class BlitzCrank : public virtual Champion
{
public:
	BlitzCrank(IMenu* Parent, IUnit* Hero);
	~BlitzCrank(); // DeConstruct this nibba


	void Combo();
	void Harass();
	void LaneClear();
	void Flee();

	auto FindBestLineCastPosition();
	auto IsInRange(Vec2 PositionA, Vec2 PositionB, float Range) -> bool;
	auto IsInRange(Vec3 PositionA, Vec3 PositionB, float Range) -> bool;
	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* BlitzCrankMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* LaneClearMenu;
	IMenu* ComboMenu;
	IMenu* HookSettings;

	IMenuOption* HookMode;
	IMenuOption* AutoHook;
	IMenuOption* UseWtoFlee;
	IMenuOption* FleeKey;
	IMenuOption* EFarm;
	IMenuOption* RFarm;

	// Draw Options
	IMenuOption* DrawHookRange;
	IMenuOption* DrawRRange; 
	IMenuOption* OnlyDrawReady;
};