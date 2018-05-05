#include "Sword.h"
#include "ItemDispatcher.h"


Sword::Sword(int pwr) : m_power(pwr)
{
}


Sword::~Sword()
{
}

void Sword::use(ItemDispatcher<GameObjTy>& dispatcher)
{
	dispatcher.dispatch(*this);
}