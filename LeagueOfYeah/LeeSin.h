#pragma once
#include "AIO.h"

class LeeSin : public virtual AIO
{
public:
	LeeSin(IUnit* Lee, IMenu* ChampMenu);
	~LeeSin(); // DeConstruct this nibba

	void Combo();
	void Harass();
	void LaneClear();
	void WardHop();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* LeeMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* LaneClearMenu;
	IMenu* HarassMenu;
	IMenu* ComboMenu;
};