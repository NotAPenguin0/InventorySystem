#pragma once

#include "IItem.h"



class HealPotion : public IItem
{
public:
	friend class ItemDispatcher<GameObjTy>;

	HealPotion(int hp);
	virtual ~HealPotion();

	virtual void use(ItemDispatcher<GameObjTy>& dispatcher) override;

private:
	int m_hp;
};

