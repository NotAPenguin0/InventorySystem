#pragma once

#include "IItem.h"


//For demonstration purposes of the Item and Inventory System
class DamagePotion : public IItem
{
public:
	DamagePotion(int damage);
	virtual ~DamagePotion();

	virtual void use(temp::GameObject* target) override;

	ATTRIBUTE_NAME("Damage Potion")
	ATTRIBUTE_ID(ItemID::DAMAGE_POTION)
	ATTRIBUTE_REUSABLE(false) //Damage potions are not reusable

private:
	int m_dmg;
};

