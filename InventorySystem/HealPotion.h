#pragma once

#include "IItem.h"



class HealPotion : public IItem
{
public:
	friend class ItemDispatcher<GameObjTy>;

	HealPotion(int hp);
	virtual ~HealPotion();

	virtual void use(ItemDispatcher<GameObjTy>& dispatcher) override;

	STRING_ATTRIBUTE(name, "Healing Potion");
	ATTRIBUTE(id, ItemID::HEAL_POTION)

private:
	int m_hp;
};

