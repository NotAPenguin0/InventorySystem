#include "IItem.h"

namespace temp
{
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
};

IItem::~IItem()
{

}