#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "AIO.h"
#include "Geom.h"

class MasterYi : public virtual Champion
{
public:
	MasterYi(IMenu* Parent, IUnit* Hero);
	~MasterYi(); // DeConstruct this nibba

	void Combo();
	void Harass();
	void LaneClear();
	void JungleClear();

	void Drawing();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* MasterYiMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* LaneClearMenu;
	IMenu* JungleMenu;
	IMenu* ComboMenu;

	IMenuOption* SmiteJung;
	IMenuOption* HealJung;
	IMenuOption* LowHP;
	IMenuOption* QJung;
	IMenuOption* EJung;
	IMenuOption* JungKey;

	IMenuOption* QLane;
	IMenuOption* ELane;

	IMenuOption* DrawQ;
	IMenuOption* VisibleOnly;

};