#pragma once
#include <algorithm>
#include "AIO.h"

class Soraka : public virtual Champion
{
public:
	Soraka(IMenu* Parent, IUnit* Hero);
	~Soraka(); //deconstruct this

	void Combo();
	void Harass();
	void LaneClear();

	//Math Needed
	std::vector<IUnit*> GetHerosNearby(bool friendly, bool enemy, float distance, IUnit* source);

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* SorakaMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* LaneClearMenu;
	IMenu* HarassMenu;
	IMenu* ComboMenu;

	IMenuOption* KillStealQ;

};