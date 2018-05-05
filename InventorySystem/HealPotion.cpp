#include "HealPotion.h"
#include "ItemDispatcher.h"

HealPotion::HealPotion(int hp) : m_hp(hp)
{
}


HealPotion::~HealPotion()
{
}

void HealPotion::use(ItemDispatcher<GameObjTy>& dispatcher)
{
	dispatcher.dispatch(*this);
}
