#pragma once

#include "IItem.h"


class Sword : public IItem
{
public:
	Sword(int pwr = 0);
	virtual ~Sword();

	STRING_ATTRIBUTE(name, "Sword")
	ATTRIBUTE(equippable, true)
	ATTRIBUTE(id, ItemID::SWORD)

	virtual void use(temp::GameObject* target) override;
	virtual void unequip(temp::GameObject* target) override;

private:
	int m_power;
};

