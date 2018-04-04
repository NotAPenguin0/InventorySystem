#pragma once

#include "IItem.h"


//For demonstration purposes of the Item and Inventory System
class DamagePotion : public IItem
{
public:
	DamagePotion(int damage);
	virtual ~DamagePotion();

	virtual void use(temp::GameObject* target) override;
	
	IMPLEMENT_ITEM_NAME("Damage Potion")
	IMPLEMENT_ITEM_ID(ItemID::DAMAGE_POTION)


private:
	int m_dmg;
};

