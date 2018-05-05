#pragma once

#include "ItemID.h"

#include <iostream>
#include <string>
#include <string_view>

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


		//etc...
	private:
		int m_hp;
		int m_power { 0 };
	};

};

/*
#define ATTRIBUTE_NAME(_name) inline virtual std::string name() override {return _name;}
#define ATTRIBUTE_ID(ID) inline virtual ItemID id() override {return ID;}
#define ATTRIBUTE_REUSABLE(reusable_) inline virtual bool reusable() override {return reusable_;}

#define BASE_ATTRIBUTE_NAME(_name) inline virtual std::string name() {return _name;}
#define BASE_ATTRIBUTE_ID(ID) inline virtual ItemID id() {return ID;}
#define BASE_ATTIRBUTE_REUSABLE(reusable_) inline virtual bool reusable() {return reusable_;}

*/


/*Watch out with this one, always double check when adding a new attribute!!*/
#define ATTRIBUTE(name, value) virtual decltype(value) name() const {return value;}
#define STRING_ATTRIBUTE(name, value) virtual std::string_view name() const {return value;}

/*Base class for Items. All Items must derive from this class. When calling use(), a target GameObject has
 *to be passed in. To give an item attributes such as a name, or an ID, you should add the ATTRIBUTE or STRING_ATTRIBUTE
 *macros somewhere in your Item class in a place where they are publicly visible. Adding support for a new attribute is
 *done simply by modifying the base IItem class in the same way you would add an attribute to the derived Items.
 *Currently supported attributes are:
 *
 *	RETURN TYPE      |      NAME        |       DEFAULT VALUE
 *	-----------------|------------------|--------------------
 *	std::string      |      name        |       "Default Item"
 *	ItemID           |      id          |       ItemID::DEFAULT_ITEM
 *	bool             |      reusable    |       false 
 *	bool             |      equippable  |       false
 *	
 *	
 *	
 *	If you don't override an attributes value, it will get the default value*/

class IItem
{
public:
	using GameObjTy = temp::GameObject;

	virtual ~IItem();

	virtual void use(temp::GameObject* target);
	virtual void unequip(GameObjTy* target);

	STRING_ATTRIBUTE(name, "Default Item")
	ATTRIBUTE(id, ItemID::DEFAULT_ITEM)
	ATTRIBUTE(reusable, false)
	ATTRIBUTE(equippable, false)

	bool is_equipped();
	void set_equip(bool eq);

private:
	bool m_equipped { false };
};





/*
#undef BASE_ATTRIBUTE_NAME
#undef BASE_ATTRIBUTE_ID
#undef BASE_ATTRIBUTE_REUSABLE

*/
