#include "DamagePotion.h"



DamagePotion::DamagePotion(int damage) : m_dmg(damage)
{
}


DamagePotion::~DamagePotion()
{
}

void DamagePotion::use(temp::GameObject* target)
{
	if (target == nullptr)
	{
		std::cout << "DamagePotion::use(GameObject* target): target was nullptr\n";
		return;
	}

	target->damage(m_dmg);
}

