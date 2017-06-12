#pragma once
#include "AIO.h"

class Ryze : public virtual Champion
{
public:
	Ryze(IMenu* Parent, IUnit* Hero);
	~Ryze(); //deconstruct this

	void Combo();
	void Harass();
	void LaneClear();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* RyzeMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* LaneClearMenu;
	IMenu* HarassMenu;
	IMenu* ComboMenu;
		
};