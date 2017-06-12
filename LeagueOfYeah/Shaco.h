#pragma once
#include "AIO.h"
#include "SDK/Vector3.h"
#include <algorithm>

class Shaco : public virtual Champion
{
public:
	Shaco(IMenu* Parent, IUnit* Hero);
	~Shaco();

	void Combo();
	void Harass();
	void Farm();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* ShacoMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* FarmMenu;
	IMenu* HarassMenu;
	IMenu* ComboMenu;

	//Draw options
	IMenuOption* DrawRRange;
	IMenuOption* DrawQRange;
	IMenuOption* DrawERange;
	IMenuOption* OnlyDrawReady;


};