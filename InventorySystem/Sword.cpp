#include "Sword.h"
#include "ItemDispatcher.h"


Sword::Sword(int pwr) : IItem(ItemID::SWORD), m_power(pwr)
{
}


Sword::~Sword()
{
}

void Sword::use(ItemDispatcher<GameObjTy>& dispatcher)
{
	dispatcher.dispatch(*this);
}