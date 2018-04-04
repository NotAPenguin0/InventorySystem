#pragma once

#include "ItemID.h"

#include <iostream>
#include <string>

namespace temp
{

	//#TEMP
	class GameObject
	{
	public:
		GameObject();
		GameObject(int hp);

		virtual void damage(int dmg);

		bool is_dead();


		//etc...
	private:
		int m_hp;
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

#define ATTRIBUTE(name, value) virtual decltype(value) name() {return value;}
#define STRING_ATTRIBUTE(name, value) virtual std::string name() {return value;}

/*Base class for Items. All Items must derive from this class. When calling use(), a target GameObject has
 *to be passed in. To give an item attributes such as a name, or an ID, you should add the ATTRIBUTE or STRING_ATTRIBUTE
 *macros somewhere in your Item class in a place where they are publicly visible. Adding support for a new attribute is
 *done simply by modifying the base IItem class in the same way you would add an attribute to the derived Items.
 *Currently supported attributes are:
 *	RETURN TYPE      |      NAME        |       DEFAULT VALUE
 *	-----------------|------------------|--------------------
 *	std::string		 |		name		|		"Default Item"
 *	ItemID			 |		id			|		ItemID::DEFAULT_ITEM
 *	bool			 |		reusable    |		false 
 *	
 *	If you don't override an attribute's value, it will get the default value*/
class IItem
{
public:
	virtual ~IItem();

	virtual void use(temp::GameObject* target) = 0;

	STRING_ATTRIBUTE(name, "Default Item")
	ATTRIBUTE(id, ItemID::DEFAULT_ITEM)
	ATTRIBUTE(reusable, false)
	
private:

};

#undef BASE_ATTRIBUTE_NAME
#undef BASE_ATTRIBUTE_ID
#undef BASE_ATTRIBUTE_REUSABLE

