#pragma once

#include "IItem.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>

template<unsigned int MAX_SIZE>
class Inventory
{
public:
	using inventory_type = std::unordered_map<std::string, std::unique_ptr<IItem>>;

	explicit Inventory(temp::GameObject* owner);
	Inventory(Inventory const& other) = delete;
	Inventory(Inventory&& other);

	inventory_type const& contents() const;
	inventory_type& contents();

	/*constructs a new item and adds it to the inventory. The id parameter will be used to access the item*/
	template<typename ItemT, typename... Args>
	void addItem(std::string const& id, Args... args)
	{
		if (m_items.size() >= ITEM_LIST_SIZE)
		{
			std::cerr << "Inventory does not have enough memory!\n";
			std::cerr << "Modify code to allow a larger inventory size\n";
		}

		m_items[id] = std::make_unique<ItemT>(std::forward<Args>(args)...);
		
	}

	void useItem(inventory_type::iterator pos, temp::GameObject* target = nullptr);
	void useItem(std::string const& name, temp::GameObject* target = nullptr);

	inventory_type::iterator getItem(std::string const& name);
	inventory_type::const_iterator getItem(std::string const& name) const;

	inventory_type::iterator begin();
	inventory_type::iterator end();

	inventory_type::const_iterator cbegin() const;
	inventory_type::const_iterator cend() const;
/*
	inventory_type::reverse_iterator rbegin();
	inventory_type::reverse_iterator rend();
*/
	void setOwner(temp::GameObject* owner);
	temp::GameObject* getOwner() const;

	const inventory_type::size_type ITEM_LIST_SIZE = MAX_SIZE;
private:
	inventory_type m_items { MAX_SIZE };
	temp::GameObject* m_owner { nullptr };
	
};

template<unsigned int MAX_SIZE>
Inventory<MAX_SIZE>::Inventory(temp::GameObject* owner) : m_owner(owner)
{
	
}

template<unsigned int MAX_SIZE>
Inventory<MAX_SIZE>::Inventory(Inventory&& other) : m_owner(std::move(other.m_owner)), m_items(std::move(other.m_items))
{
	other.m_owner = nullptr;
	other.m_items = inventory_type {};
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type const& Inventory<MAX_SIZE>::contents() const
{
	return m_items;
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type& Inventory<MAX_SIZE>::contents()
{
	return m_items;
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::iterator Inventory<MAX_SIZE>::begin() { return m_items.begin(); }

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::iterator Inventory<MAX_SIZE>::end()
{
	return m_items.end();
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::const_iterator Inventory<MAX_SIZE>::cbegin() const { return m_items.cbegin(); }
template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::const_iterator Inventory<MAX_SIZE>::cend() const { return m_items.cend(); }

/*
template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::reverse_iterator Inventory<MAX_SIZE>::rbegin() { return m_items.rbegin(); }
template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::reverse_iterator Inventory<MAX_SIZE>::rend() { return m_items.rend(); }
*/

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::iterator Inventory<MAX_SIZE>::getItem(std::string const& name)
{
	return m_items.find(name);
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::const_iterator Inventory<MAX_SIZE>::getItem(std::string const& name) const
{
	return m_items.find(name);
}

template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::useItem(std::string const& name, temp::GameObject* target)
{
	useItem(getItem(name), target);
}


template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::useItem(inventory_type::iterator pos, temp::GameObject* target)
{


	//use the item
	auto& it = *pos;
	auto& item = it.second;

	if (item->equippable())
	{
		if (!item->is_equipped())
		{
			item->set_equip();
			item->use(m_owner);
		}
		return;
	}
	else
	{
		item->use(target);
	}

	if (!item->reusable())
		m_items.erase(pos);
}

template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::setOwner(temp::GameObject* owner)
{
	m_owner = owner;
}

template<unsigned int MAX_SIZE>
temp::GameObject* Inventory<MAX_SIZE>::getOwner() const
{
	return m_owner;
}
