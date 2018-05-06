#include "DamagePotion.h"
#include "ItemDispatcher.h"

DamagePotion::DamagePotion(int damage) : IItem(ItemID::DAMAGE_POTION), m_dmg(damage)
{
}


DamagePotion::~DamagePotion()
{
}

void DamagePotion::use(ItemDispatcher<GameObjTy>& dispatcher)
{
	dispatcher.dispatch(*this);
}
