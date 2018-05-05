#include "DamagePotion.h"
#include "ItemDispatcher.h"

DamagePotion::DamagePotion(int damage) : m_dmg(damage)
{
}


DamagePotion::~DamagePotion()
{
}

void DamagePotion::use(ItemDispatcher<GameObjTy>& dispatcher)
{
	dispatcher.dispatch(*this);
}
