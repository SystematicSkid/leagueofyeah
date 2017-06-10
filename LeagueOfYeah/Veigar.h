#pragma once
#include "AIO.h"
#include "SDK/Vector3.h"

class Veigar : public virtual Champion
{
public:
	Veigar(IMenu* Parent, IUnit* Hero);
	~Veigar();

	void Combo();
	void Harass();
	void Farm();
	void RCast();

	void OnGameUpdate();
	void OnRender();
	void OnSpellCast(CastedSpell const& Args);
	void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);

private:
	IMenu* VeigarMenu;
	IMenu* Drawings;
	IMenu* Misc;
	IMenu* FarmMenu;
	IMenu* HarassMenu;
	IMenu* ComboMenu;
	IMenu* RCastMenu;

	//Draw options
	IMenuOption* DrawRRange;
	IMenuOption* DrawQRange;
	IMenuOption* DrawERange;
	IMenuOption* OnlyDrawReady;
	

};