#include "HealPotion.h"

HealPotion::HealPotion(int hp) : m_hp(hp)
{
}


HealPotion::~HealPotion()
{
}

void HealPotion::use(temp::GameObject* target)
{
	if (target == nullptr)
	{
		std::cerr << "Target was nullptr\n";
		return;
	}

	target->damage(-m_hp);
}
