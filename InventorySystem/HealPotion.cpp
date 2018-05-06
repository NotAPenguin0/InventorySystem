#include "HealPotion.h"
#include "ItemDispatcher.h"

HealPotion::HealPotion(int hp) : IItem(ItemID::HEAL_POTION), m_hp(hp)
{
}


HealPotion::~HealPotion()
{
}

void HealPotion::use(ItemDispatcher<GameObjTy>& dispatcher)
{
	dispatcher.dispatch(*this);
}
