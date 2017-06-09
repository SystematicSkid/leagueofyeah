#include "BlitzCrank.h"

BlitzCrank::~BlitzCrank() // We dont want our script to stay around
{
	BlitzCrankMenu->Remove();
}

BlitzCrank::BlitzCrank(IMenu* Parent, IUnit* Hero) :Champion(Parent, Hero)
{
	if (Q == nullptr)
	{
		// Do hook memes here
	}
}