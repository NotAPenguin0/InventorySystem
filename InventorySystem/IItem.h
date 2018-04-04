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

class IItem
{
public:
	virtual ~IItem();

	virtual void use(temp::GameObject* target) = 0;

	BASE_ATTRIBUTE_NAME("Default Item")
	BASE_ATTRIBUTE_ID(ItemID::DEFAULT_ITEM)
	BASE_ATTIRBUTE_REUSABLE(false)
	
private:

};

#undef BASE_ATTRIBUTE_NAME
#undef BASE_ATTRIBUTE_ID
#undef BASE_ATTRIBUTE_REUSABLE

