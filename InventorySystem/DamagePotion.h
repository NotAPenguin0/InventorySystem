#pragma once

#include "IItem.h"


//For demonstration purposes of the Item and Inventory System
class DamagePotion : public IItem
{
public:
	friend class ItemDispatcher<GameObjTy>;

	DamagePotion(int damage);
	virtual ~DamagePotion();

	virtual void use(ItemDispatcher<GameObjTy>& dispatcher) override;

	STRING_ATTRIBUTE(name, "Damage Potion")
	ATTRIBUTE(id, ItemID::DAMAGE_POTION)
	ATTRIBUTE(reusable, false)

private:
	int m_dmg;
};

