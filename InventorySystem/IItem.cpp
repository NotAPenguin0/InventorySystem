#include "IItem.h"

#define ASSERT(condition, message) \
if (condition) {} \
else \
{\
	std::cerr << "Assertion failed: " << #message << "\n"; \
}

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



IItem::IItem(ItemID id, std::bitset<ATTRIBUTE_COUNT> attributes /* = std::bitset<ATTRIBUTE_COUNT> {}*/)
	: m_id { id }
{
	m_attributes[EQUIPPABLE_POS] = attributes[EQUIPPABLE_POS];
	m_attributes[STACKABLE_POS] = attributes[STACKABLE_POS];
	m_attributes[REUSABLE_POS] = attributes[REUSABLE_POS];
	m_attributes[EQUIPPED_POS] = false;

	ASSERT(!(equippable() && stackable()), "An item cannot be stackable and equippable at the same time");
}

IItem::~IItem()
= default;

void IItem::set_equip(bool eq)
{
	m_attributes[EQUIPPED_POS] = eq;
}

bool IItem::is_equipped()
{
	return m_attributes.test(EQUIPPED_POS);
}

bool IItem::equippable()
{
	return m_attributes.test(EQUIPPABLE_POS);
}

bool IItem::reusable()
{
	return m_attributes.test(REUSABLE_POS);
}

bool IItem::stackable()
{
	return m_attributes.test(STACKABLE_POS);
}

ItemID IItem::id()
{
	return m_id;
}

void IItem::setEquippable(bool eq)
{
	m_attributes[EQUIPPABLE_POS] = eq;
}

void IItem::setStackable(bool stack)
{
	m_attributes[STACKABLE_POS] = stack;
}

void IItem::setReusable(bool reuse)
{
	m_attributes[REUSABLE_POS] = reuse;
}