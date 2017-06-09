#pragma once
#include "AIO.h"

class Zilean : public virtual Champion
{
public:
	Zilean(IMenu* Parent, IUnit* Hero);
	~Zilean(); // DeConstruct this nibba

	void Combo();
	void Harass();
	void LaneClear();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* ZileanMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* LaneClearMenu;
	IMenu* HarassMenu;
	IMenu* ComboMenu;

	
};