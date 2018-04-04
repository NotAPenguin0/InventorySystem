#include "IItem.h"

namespace temp
{
	GameObject::GameObject() : m_hp(-1)
	{

	}

	GameObject::GameObject(int hp) : m_hp(hp)
	{
		std::cout << "Creating GameObject with " << hp << " health\n";
	}

	void GameObject::damage(int dmg)
	{
		m_hp -= dmg;
		std::cout << "GameObject got damaged: -" << dmg << "HP. GameObject has " << m_hp << "HP left\n";
		if (is_dead())
		{
			std::cout << "GameObject has died!\n";
		}
	}

	bool GameObject::is_dead()
	{
		return m_hp < 0;
	}

	void GameObject::add_power(int extra_pwr)
	{
		m_power += extra_pwr;
		std::cout << "GameObject got extra power: +" << extra_pwr << "\nNew power is " << m_power << "\n";
	}
};

IItem::~IItem()
{

}

bool IItem::is_equipped()
{
	return m_equipped;
}

void IItem::set_equip()
{
	m_equipped = true;
}