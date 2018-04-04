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

#define IMPLEMENT_ITEM_NAME(_name) inline virtual std::string name() override {return #_name;}
#define IMPLEMENT_ITEM_ID(ID) inline virtual ItemID id() override {return ID;}

class IItem
{
public:
	virtual ~IItem();

	virtual void use(temp::GameObject* target) = 0;

	virtual std::string name() = 0;
	virtual ItemID id() = 0;

private:


};

