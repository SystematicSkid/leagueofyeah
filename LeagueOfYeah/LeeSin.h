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
	//general menu settings
	IMenu* LeeMenu;

	//draw menu settings
	IMenu* Drawings;

	//misc menu settings
	IMenu* Misc;

	//laneclear menu settings
	IMenu* LaneClearMenu;

	//harass menu settings
	IMenu* HarassMenu;

	//combo menu settings
	IMenu* ComboMenu;

};