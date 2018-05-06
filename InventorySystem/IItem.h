#pragma once

#include "ItemID.h"

#include <iostream>
#include <string>
#include <string_view>
#include <bitset>

namespace temp
{

	//#TEMP
	class GameObject
	{
	public:
		GameObject();
		GameObject(int hp);

		//pass negative dmg parameter to heal
		virtual void damage(int dmg);

		bool is_dead();

		virtual void add_power(int extra_pwr);

		inline int getHealth() { return m_hp; }

		//etc...
	private:
		int m_hp;
		int m_power { 0 };
	};

};


/*Watch out with this one, always double check when adding a new attribute!!*/
#define ATTRIBUTE(name, value) virtual decltype(value) name() const {return value;}
#define STRING_ATTRIBUTE(name, value) virtual std::string_view name() const {return value;}

/*Base class for Items. All Items must derive from this class. When calling use(), a target GameObject has
 *to be passed in. To give an item attributes such as a name, or an ID, you should add the ATTRIBUTE or STRING_ATTRIBUTE
 *macros somewhere in your Item class in a place where they are publicly visible. Adding support for a new attribute is
 *done simply by modifying the base IItem class in the same way you would add an attribute to the derived Items.
 *Currently supported attributes are:
 *
 *	RETURN TYPE      |      NAME        |       DEFAULT VALUE          | Position in attributes bitset
 *	-----------------|------------------|------------------------------|------------------------------
 *	ItemID           |      id          |       ItemID::DEFAULT_ITEM   |              None
 *	bool             |      reusable    |       false                  |              1 
 *	bool             |      equippable  |       false                  |              0
 *	bool             |      stackable   |       true                   |              2
 *	
 *	
 *	If you don't override an attributes value, it will get the default value*/

template<typename GameObjTy>
class ItemDispatcher;

class IItem
{
public:
	static const int ATTRIBUTE_COUNT = 3; /*3 because isEquipped is not an attribute that the user can set*/

	using GameObjTy = temp::GameObject;

	friend class ItemDispatcher<GameObjTy>;
	
	IItem(ItemID id, std::bitset<ATTRIBUTE_COUNT> attributes = std::bitset<ATTRIBUTE_COUNT> {});
	virtual ~IItem();

	virtual void use(ItemDispatcher<GameObjTy>& dispatcher) = 0;

	bool reusable();
	bool stackable();
	bool equippable();
	bool is_equipped();

	ItemID id();

	void set_equip(bool eq);

private:
	static const std::size_t EQUIPPABLE_POS = 0;
	static const std::size_t REUSABLE_POS = 1;
	static const std::size_t STACKABLE_POS = 2;
	static const std::size_t EQUIPPED_POS = 3;

	ItemID m_id;
	std::bitset<ATTRIBUTE_COUNT> m_attributes;
};





/*
#undef BASE_ATTRIBUTE_NAME
#undef BASE_ATTRIBUTE_ID
#undef BASE_ATTRIBUTE_REUSABLE

*/
