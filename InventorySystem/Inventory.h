#pragma once

#include "IItem.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include <string_view>

template<unsigned int MAX_SIZE>
class Inventory
{
public:
	class Exception
	{
	private:
		std::string msg;
	public:
		explicit inline Exception(std::string const& error)  msg {error} {}
		inline std::string_view what() { return msg; }
	};

	using game_object_type = temp::GameObject; //#IMPORTANT: Modify this to be the type of your GameObject
	using item_type = IItem; //#IMPORTANT: Modify this to be the type of your Item interface class

	using game_object_pointer = game_object_type*;
	using inventory_type = std::unordered_map<std::string, std::unique_ptr<item_type>>;
	using iterator = inventory_type::iterator;
	using const_iterator = inventory_type::const_iterator;
	using size_type = inventory_type::size_type;

	explicit Inventory(game_object_pointer owner);
	Inventory(Inventory const& other) = delete;
	Inventory(Inventory&& other);

	Inventory& operator=(Inventory const& other) = delete;
	Inventory& operator=(Inventory&& other);

	inventory_type const& contents() const;
	inventory_type& contents();

	/*constructs a new item and adds it to the inventory. The id parameter will be used to access the item*/
	template<typename ItemT, typename... Args>
	void addItem(std::string const& id, Args... args)
	{
		if (m_items.size() >= ITEM_LIST_SIZE)
		{
			throw InventoryFullException();
		}

		m_items[id] = std::make_unique<ItemT>(std::forward<Args>(args)...);
		
	}

	void useItem(std::string const& name, game_object_pointer target = nullptr);

	/*The iterators invalidate when a new Item is added to the inventory*/
	iterator getItem(std::string const& name);
	/*The iterators invalidate when a new Item is added to the inventory*/
	const_iterator getItem(std::string const& name) const;

	void removeItem(std::string const& name);

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	size_type max_size() const;
	size_type size() const;

	/*Merges inventory A with this inventory. Leaves other empty, unless this inventory is full, in which case the leftover
	  elements will be deleted*/ //#TODO: leftover elements are left in old inventory?
	template<unsigned int N>
	void merge(Inventory<N>& other);

	template<unsigned int N>
	bool merge_fits(Inventory<N> const& other);

	/*Transfers item with name parameter into the inventory specified in destination, unless destination does not have enough
	 *space left*/
	template<unsigned int N>
	void transfer(Inventory<N>& destination, std::string const& name);

	bool empty() const;
	bool full() const;

	void setOwner(game_object_pointer owner);
	game_object_pointer getOwner() const;

	const size_type ITEM_LIST_SIZE = MAX_SIZE;

private:
	inventory_type m_items { MAX_SIZE };
	game_object_pointer m_owner { nullptr };

	//these functions are private so you cannot accidentally pass an invalid iterator to one of these, causing undefined behavior

	void useItem(iterator pos, game_object_pointer target = nullptr); 
	void removeItem(iterator pos);
	
	Exception InventoryFullException() { return Exception {"Inventory is full"}; }
};

template<unsigned int MAX_SIZE>
Inventory<MAX_SIZE>::Inventory(game_object_pointer owner) : m_owner(owner)
{
	
}

template<unsigned int MAX_SIZE>
Inventory<MAX_SIZE>::Inventory(Inventory&& other) : m_owner(std::move(other.m_owner)), m_items(std::move(other.m_items))
{
	other.m_owner = nullptr;
	other.m_items = inventory_type {};
}

template<unsigned int MAX_SIZE>
Inventory<Max_SIZE>& Inventory<MAX_SIZE>::operator=(Inventory<MAX_SIZE>&& other)
{
	m_owner = other.m_owner;
	m_items = std::move(other.m_items);

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
typename Inventory<MAX_SIZE>::iterator Inventory<MAX_SIZE>::begin() { return m_items.begin(); }

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::iterator Inventory<MAX_SIZE>::end()
{
	return m_items.end();
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::const_iterator Inventory<MAX_SIZE>::cbegin() const { return m_items.cbegin(); }
template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::const_iterator Inventory<MAX_SIZE>::cend() const { return m_items.cend(); }

/*
template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::reverse_iterator Inventory<MAX_SIZE>::rbegin() { return m_items.rbegin(); }
template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::inventory_type::reverse_iterator Inventory<MAX_SIZE>::rend() { return m_items.rend(); }
*/

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::iterator Inventory<MAX_SIZE>::getItem(std::string const& name)
{
	return m_items.find(name);
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::const_iterator Inventory<MAX_SIZE>::getItem(std::string const& name) const
{
	return m_items.find(name);
}

template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::useItem(std::string const& name, game_object_pointer target)
{
	useItem(getItem(name), target);
}


template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::useItem(iterator pos, game_object_pointer target)
{
	//use the item
	auto& it = *pos;
	auto& item = it.second;

	if (item->equippable())
	{
		if (!item->is_equipped())
		{
			item->set_equip(true);
			item->use(m_owner);
		}
		else
		{
			item->set_equip(false);
			item->unequip(m_owner);
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
void Inventory<MAX_SIZE>::removeItem(iterator pos)
{

	m_items.erase(pos);
}

template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::removeItem(std::string const& name)
{
	removeItem(getItem(name));
}

template<unsigned int MAX_SIZE>
void Inventory<MAX_SIZE>::setOwner(game_object_pointer owner)
{
	m_owner = owner;
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::game_object_pointer Inventory<MAX_SIZE>::getOwner() const
{
	return m_owner;
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::size_type Inventory<MAX_SIZE>::max_size() const
{
	return ITEM_LIST_SIZE;
}

template<unsigned int MAX_SIZE>
typename Inventory<MAX_SIZE>::size_type Inventory<MAX_SIZE>::size() const
{
	return m_items.size();
}

template<unsigned int MAX_SIZE>
template<unsigned int N>
void Inventory<MAX_SIZE>::merge(Inventory<N>& other)
{

	if (!merge_fits(other))
		throw InventoryFullException();

	for (auto& it = other.begin(); it != other.end(); std::advance(it, 1))
	{

		this->m_items[it->first] = std::move(it->second);
	}

	other.contents().clear();
}

template<unsigned int MAX_SIZE>
template<unsigned int N>
bool Inventory<MAX_SIZE>::merge_fits(Inventory<N> const& other)
{
	return !(full() || other.size() + this->size() >= max_size());
}

template<unsigned int MAX_SIZE>
template<unsigned int N>
void Inventory<MAX_SIZE>::transfer(Inventory<N>& destination, std::string const& name)
{	

	if (destination.full())
		return;

	auto& it = getItem(name);
	auto& item = (*it).second;

	destination.contents()[name] = std::move(item);

	m_items.erase(it);
}

template<unsigned int MAX_SIZE>
bool Inventory<MAX_SIZE>::empty() const
{
	return m_items.empty();
}

template<unsigned int MAX_SIZE>
bool Inventory<MAX_SIZE>::full() const
{
	return max_size() <= size();
}