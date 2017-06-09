#pragma once
#include "SDK\PluginSDK.h"

struct EnemyTeleportInformation
{
	IUnit*	Player;
	bool IsRecalling;
	float CompletionTime;

	float LastSeenTime;
	float MovementRadius;
	std::vector<Vec3> WayPts;
};

enum Champions
{
	KOGMAW, CAITLYN, TWITCH, GRAVES, TRISTANA, SIVIR, LUCIAN
};

class Champion
{
public:
	Champion(IMenu* Parent, IUnit* Hero) :Hero(Hero), ParentMenu(Parent) {}
	~Champion();

	IUnit * GetHero();
	IMenu* GetMenu();

	virtual void Combo() {};
	//events
	virtual void OnGameUpdate();
	virtual void OnRender();
	virtual void OnRealSpellCast(CastedSpell const& Args);
	virtual void OnSpellCast(CastedSpell const& Args);
	virtual bool OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition);
	virtual void OnOrbwalkAttack(IUnit* Source, IUnit* Target);
	virtual void BeforeAttack(IUnit* Target);
	virtual void OnInterruptible(InterruptibleSpell const& Args);
	virtual void OnGapCloser(GapCloserSpell const& Args);
	virtual void OnLevelUp(IUnit* Source, int NewLevel);
	virtual void OnPlayAnimation(IUnit* Source, std::string const Args);
	virtual void OnExitVisible(IUnit* Source);
	virtual void OnTeleport(OnTeleportArgs* Args);

protected:
	std::vector<IUnit*>	EnemyHeros;
	IUnit*			Hero;
	IMenu*			ParentMenu;
	ISpell2*		Q;
	ISpell2*		W;
	ISpell2*		E;
	ISpell2*		R;
	short			keystate;
	IUnit*			ComboTarget;
	bool			SemiManualKey;
};