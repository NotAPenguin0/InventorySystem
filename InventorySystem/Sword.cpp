#include "Sword.h"



Sword::Sword(int pwr) : m_power(pwr)
{
}


Sword::~Sword()
{
}

void Sword::use(temp::GameObject* target)
{
	target->add_power(m_power);
}
