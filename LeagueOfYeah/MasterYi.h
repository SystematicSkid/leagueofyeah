#pragma once
#include "AIO.h"

class MasterYi : public virtual Champion
{
public:
	MasterYi(IMenu* Parent, IUnit* Hero);
	~MasterYi(); // DeConstruct this nibba

	void Combo();
	void Harass();
	void LaneClear();
	void JungleClear();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	//general menu settings
	IMenu* MasterYiMenu;

	//draw menu settings
	IMenu* Drawings;

	//misc menu settings
	IMenu* Misc;

	//laneclear menu settings
	IMenu* LaneClearMenu;

	//harass menu settings
	IMenu* JungleMenu;

	//combo menu settings
	IMenu* ComboMenu;

	IMenuOption* SmiteJung;
	IMenuOption* HealJung;
	IMenuOption* LowHP;
	IMenuOption* QJung;
	IMenuOption* EJung;

};