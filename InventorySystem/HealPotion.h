#pragma once

#include "IItem.h"

class HealPotion : public IItem<>
{
public:
	HealPotion(int hp);
	virtual ~HealPotion();

	STRING_ATTRIBUTE(name, "Healing Potion");
	ATTRIBUTE(id, ItemID::HEAL_POTION)

	virtual void use(temp::GameObject* target) override;

private:
	int m_hp;
};

