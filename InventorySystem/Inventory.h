#pragma once

#include "IItem.h"
#include <list>
#include <memory>

class Inventory
{
public:
	Inventory(temp::GameObject* owner);
	Inventory(Inventory const& other);
	Inventory(Inventory&& other);
private:
	std::list<std::unique_ptr<IItem>> m_items;
	temp::GameObject* m_owner;
};
