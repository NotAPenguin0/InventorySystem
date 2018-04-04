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
		GameObject(int hp);

		virtual void damage(int dmg);

		bool is_dead();


		//etc...
	private:
		int m_hp;
	};

};

#define ATTRIBUTE_NAME(_name) inline virtual std::string name() override {return _name;}
#define ATTRIBUTE_ID(ID) inline virtual ItemID id() override {return ID;}
#define ATTRIBUTE_REUSABLE(reusable_) inline virtual bool reusable() override {return reusable_;}

#define BASE_ATTRIBUTE_NAME(_name) inline virtual std::string name() {return _name;}
#define BASE_ATTRIBUTE_ID(ID) inline virtual ItemID id() {return ID;}
#define BASE_ATTIRBUTE_REUSABLE(reusable_) inline virtual bool reusable() {return reusable_;}

#define ATTRIBUTE(name, value) virtual decltype(value) name() {return value;}
#define STRING_ATTRIBUTE(name, value) virtual std::string name() {return value;}

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

