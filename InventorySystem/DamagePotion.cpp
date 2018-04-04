#include "DamagePotion.h"



DamagePotion::DamagePotion(int damage) : m_dmg(damage)
{
}


DamagePotion::~DamagePotion()
{
}

void DamagePotion::use(temp::GameObject* target)
{
	target->damage(m_dmg);
}

