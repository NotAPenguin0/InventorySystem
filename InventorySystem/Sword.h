#pragma once

#include "IItem.h"

template<typename GameObjTy>
class ItemDispatcher;

class Sword : public IItem
{
public:

	friend class ItemDispatcher<GameObjTy>;

	Sword(int pwr = 0);
	virtual ~Sword();

	virtual void use(ItemDispatcher<GameObjTy>& dispatcher) override;


	STRING_ATTRIBUTE(name, "Sword")
	ATTRIBUTE(equippable, true)
	ATTRIBUTE(id, ItemID::SWORD)

private:
	int m_power;
};

