#pragma once

#include "IItemDispatcher.h"
#include "Items.h"

template<typename GameObjTy>
class ItemDispatcher : public IItemDispatcher<GameObjTy>
{
public:
	ItemDispatcher(GameObjTy* target);
	~ItemDispatcher();

	void dispatch(IItem& item);
	void dispatch(HealPotion& item);
	void dispatch(DamagePotion& item);
	void dispatch(Sword& item);
};

template<typename GameObjTy>
ItemDispatcher<GameObjTy>::ItemDispatcher(GameObjTy* target) : IItemDispatcher<GameObjTy> { target }
{

}

template<typename GameObjTy>
ItemDispatcher<GameObjTy>::~ItemDispatcher() = default;

template<typename GameObjTy>
void ItemDispatcher<GameObjTy>::dispatch(IItem& item)
{
	/*Default item does not have any effects*/
}

template<typename GameObjTy>
void ItemDispatcher<GameObjTy>::dispatch(HealPotion& item)
{
	target()->damage(-item.m_hp);
}

template<typename GameObjTy>
void ItemDispatcher<GameObjTy>::dispatch(DamagePotion& item)
{
	target()->damage(item.m_dmg);
}

template<typename GameObjTy>
void ItemDispatcher<GameObjTy>::dispatch(Sword& item)
{
	if (!item.is_equipped())
		target()->add_power(item.m_power);
	else target()->add_power(-item.m_power);
}
