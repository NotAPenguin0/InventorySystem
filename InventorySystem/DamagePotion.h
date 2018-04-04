#pragma once

#include "IItem.h"


//For demonstration purposes of the Item and Inventory System
class DamagePotion : public IItem
{
public:
	DamagePotion(int damage);
	virtual ~DamagePotion();

	virtual void use(temp::GameObject* target) override;

	STRING_ATTRIBUTE(name, "Damage Potion")
	ATTRIBUTE(id, ItemID::DEFAULT_ITEM)
	ATTRIBUTE(reusable, false)

private:
	int m_dmg;
};

