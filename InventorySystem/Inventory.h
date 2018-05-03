#pragma once

#include "IItem.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include <string_view>
#include <type_traits>

template<unsigned int MAX_SIZE, typename GameObjTy = temp::GameObject, typename ItemTy = IItem>
class Inventory
{
private:

	class Traits //class to simulate namespace inside class
	{
	public:
		/*HasUseMethod type trait*/
		
		template<typename _Ty, typename = std::void_t<>>
		struct HasUseMethodHelper : std::false_type 
		{
		};

		template<typename _Ty>
		struct HasUseMethodHelper<_Ty, std::void_t<decltype(std::declval<_Ty>().use(std::declval<GameObjTy*>()))>> : std::true_type
		{
		};

		template<typename _Ty>
		struct HasUseMethodT : HasUseMethodHelper<_Ty>::type
		{
		};

		template<typename _Ty> using HasUseMethod = typename HasUseMethodT<_Ty>::type;
		template<typename _Ty> static constexpr bool HasUseMethodV = HasUseMethod<_Ty>::value;
		
		/*HasEquippabmeMethod type trait*/
		
		template<typename _Ty, std::void_t<>>
		struct HasEquippableMethodHelper : std::false_type
		{
		};
		
		template<typename _Ty>
		struct HasEquippableMethodHelper<_Ty, 
			std::void_t<decltype(std::is_same_v<std::declval<_Ty>().equippable(), bool >)>> : std::true_type
		{
		};
		
		template<typename _Ty>
		struct HasEquippableMethodT : HasEquippableMethodHelper<_Ty>::type
		{
		};
		
		template<typename _Ty> using HasEquippableMethod = typename HasEquippableMethodT<_Ty>::type;
		template<typename _Ty> static constexpr bool HasEquippableMethodV = HasEquippableMethod<_Ty>::value;
		
		/*HasIsEquipped type trait*/
		
		template<typename _Ty, std::void_t<>>
		struct HasIsEquippedMethodHelper : std::false_type
		{
		};
		
		template<typename _Ty>
		struct HasIsEquippedMethodHelper<_Ty, 
			std::void_t<decltype(std::is_same_v<std::declval<_Ty>().is_equipped(), bool >)>> : std::true_type
		{
		};
		
		template<typename _Ty>
		struct HasIsEquippedMethodT : HasIsEquippedMethodHelper<_Ty>::type
		{
		};
		
		template<typename _Ty> using HasIsEquippedMethod = typename HasIsEquippedMethodT<_Ty>::type;
		template<typename _Ty> static constexpr bool HasIsEquippedMethodV = HasIsEquippedMethod<_Ty>::value;
		
		/*HasSetEquip type trait*/
		
		template<typename _Ty, std::void_t<>>
		struct HasSetEquipMethodHelper : std::false_type
		{
		};
		
		template<typename _Ty>
		struct HasSetEquipMethodHelper<_Ty, 
			std::void_t<decltype(std::is_same_v<std::declval<_Ty>().set_equip(std::declval<bool>()), void >)>> 
				: std::true_type
		{
		};
		
		template<typename _Ty>
		struct HasSetEquipMethodT : HasSetEquipMethodHelper<_Ty>::type
		{
		};
		
		template<typename _Ty> using HasSetEquipMethod = typename HasSetEquipMethodT<_Ty>::type;
		template<typename _Ty> static constexpr bool HasSetEquipMethodV = HasSetEquipMethod<_Ty>::value;
		
		/*HasUnequipMethod type trait*/
		
		template<typename _Ty, std::void_t<>>
		struct HasUnequipMethodHelper : std::false_type
		{
		};
		
		template<typename _Ty>
		struct HasUnequipMethodHelper<_Ty, 
			std::void_t<decltype(std::is_same_v<std::declval<_Ty>().unequip(std::declval<GameObjTy*>()), void >)>> 
				: std::true_type
		{
		};
		
		template<typename _Ty>
		struct HasUnequipMethodT : HasUnequipMethodHelper<_Ty>::type
		{
		};
		
		template<typename _Ty> using HasUnequipMethod = typename HasUnequipMethodT<_Ty>::type;
		template<typename _Ty> static constexpr bool HasUnequipMethodV = HasUnequipMethod<_Ty>::value;
		
		/*HasReusableMethod type trait*/
		
		template<typename _Ty, std::void_t<>>
		struct HasReusableMethodHelper : std::false_type
		{
		};
		
		template<typename _Ty>
		struct HasReusableMethodHelper<_Ty, 
			std::void_t<decltype(std::is_same_v<std::declval<_Ty>().reusable(), bool >)>> 
				: std::true_type
		{
		};
		
		template<typename _Ty>
		struct HasReusableMethodT : HasReusableMethodHelper<_Ty>::type
		{
		};
		
		template<typename _Ty> using HasReusableMethod = typename HasReusableMethodT<_Ty>::type;
		template<typename _Ty> static constexpr bool HasReusableMethodV = HasReusableMethod<_Ty>::value;
		

		template<typename _Ty>
		struct IsValidItemT
		{
			static constexpr bool value =
				HasEquippableMethodV<_Ty>
				&& HasUseMethodV<_Ty>
				&& HasIsEquippedMethodV<_Ty>
				&& HasSetEquipMethodV<_Ty>
				&& HasEquippableMethodV<_Ty>
				&& HasReusableMethodV<_Ty>;
		};
		
		template<typename _Ty> using IsValidItem = typename IsValidItemT<_Ty>::type;
		template<typename _Ty> static constexpr bool IsValidItemV = IsValidItemT<_Ty>::value;
	};

public:
	static_assert(Traits::IsValidItemV<ItemTy>, "Item type is invalid. It should provide methods listed in documentation");
	

	class Exception
	{
	private:
		std::string msg;
	public:
		explicit inline Exception(std::string const& error) : msg {error} {}
		inline std::string_view what() { return msg; }
	};

	using game_object_type = GameObjTy; 
	using item_type = ItemTy; 
	using item_pointer = std::unique_ptr<item_type>;

	using game_object_pointer = game_object_type*;
	using inventory_type = std::unordered_map<std::string, item_pointer>;
	using iterator = typename inventory_type::iterator;
	using const_iterator = typename inventory_type::const_iterator;
	using size_type = typename inventory_type::size_type;

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
		if constexpr (!std::is_base_of_v<item_type, ItemT>)
			throw InvalidItemTypeException();

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
	void merge(Inventory<N, GameObjTy, ItemTy>& other);

	template<unsigned int N>
	bool merge_fits(Inventory<N, GameObjTy, ItemTy> const& other);

	/*Transfers item with name parameter into the inventory specified in destination, unless destination does not have enough
	 *space left*/
	template<unsigned int N>
	void transfer(Inventory<N, GameObjTy, ItemTy>& destination, std::string const& name);

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
	
	inline Exception InventoryFullException() { return Exception {"Inventory is full"}; }
	inline Exception InvalidItemTypeException() { return Exception {"Item type must be derived from Inventory::ItemTy, which defaults to IItem"}; }
};

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
Inventory<MAX_SIZE, GameObjTy, ItemTy>::Inventory(game_object_pointer owner) : m_owner(owner)
{
	
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
Inventory<MAX_SIZE, GameObjTy, ItemTy>::Inventory(Inventory&& other) : m_owner(std::move(other.m_owner)), m_items(std::move(other.m_items))
{
	other.m_owner = nullptr;
	other.m_items = inventory_type {};
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
Inventory<MAX_SIZE, GameObjTy, ItemTy>& Inventory<MAX_SIZE, GameObjTy, ItemTy>::operator=(Inventory<MAX_SIZE, GameObjTy, ItemTy>&& other)
{

	m_owner = other.m_owner;
	m_items = std::move(other.m_items);

	other.m_owner = nullptr;
	other.m_items = inventory_type {};

	return *this;
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::inventory_type const& Inventory<MAX_SIZE, GameObjTy, ItemTy>::contents() const
{
	return m_items;
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::inventory_type& Inventory<MAX_SIZE, GameObjTy, ItemTy>::contents()
{
	return m_items;
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::iterator Inventory<MAX_SIZE, GameObjTy, ItemTy>::begin() { return m_items.begin(); }

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::iterator Inventory<MAX_SIZE, GameObjTy, ItemTy>::end()
{
	return m_items.end();
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::const_iterator Inventory<MAX_SIZE, GameObjTy, ItemTy>::cbegin() const { return m_items.cbegin(); }
template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::const_iterator Inventory<MAX_SIZE, GameObjTy, ItemTy>::cend() const { return m_items.cend(); }

/*
template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory< MAX_SIZE, GameObjTy, ItemTy>::inventory_type::reverse_iterator Inventory< MAX_SIZE, GameObjTy, ItemTy>::rbegin() { return m_items.rbegin(); }
template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory< MAX_SIZE, GameObjTy, ItemTy>::inventory_type::reverse_iterator Inventory< MAX_SIZE, GameObjTy, ItemTy>::rend() { return m_items.rend(); }
*/

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::iterator Inventory<MAX_SIZE, GameObjTy, ItemTy>::getItem(std::string const& name)
{
	return m_items.find(name);
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::const_iterator Inventory<MAX_SIZE, GameObjTy, ItemTy>::getItem(std::string const& name) const
{
	return m_items.find(name);
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::useItem(std::string const& name, game_object_pointer target)
{
	useItem(getItem(name), target);
}


template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::useItem(iterator pos, game_object_pointer target)
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

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::removeItem(iterator pos)
{

	m_items.erase(pos);
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::removeItem(std::string const& name)
{
	removeItem(getItem(name));
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::setOwner(game_object_pointer owner)
{
	m_owner = owner;
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::game_object_pointer Inventory<MAX_SIZE, GameObjTy, ItemTy>::getOwner() const
{
	return m_owner;
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::size_type Inventory<MAX_SIZE, GameObjTy, ItemTy>::max_size() const
{
	return ITEM_LIST_SIZE;
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
typename Inventory<MAX_SIZE, GameObjTy, ItemTy>::size_type Inventory<MAX_SIZE, GameObjTy, ItemTy>::size() const
{
	return m_items.size();
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
template<unsigned int N>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::merge(Inventory<N, GameObjTy, ItemTy>& other)
{

	if (!merge_fits(other))
		throw InventoryFullException();

	for (auto& it = other.begin(); it != other.end(); std::advance(it, 1))
	{

		this->m_items[it->first] = std::move(it->second);
	}

	other.contents().clear();
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
template<unsigned int N>
bool Inventory<MAX_SIZE, GameObjTy, ItemTy>::merge_fits(Inventory<N, GameObjTy, ItemTy> const& other)
{
	return !(full() || other.size() + this->size() >= max_size());
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
template<unsigned int N>
void Inventory<MAX_SIZE, GameObjTy, ItemTy>::transfer(Inventory<N, GameObjTy, ItemTy>& destination, std::string const& name)
{	

	if (destination.full())
		return;

	auto& it = getItem(name);
	auto& item = (*it).second;

	destination.contents()[name] = std::move(item);

	m_items.erase(it);
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
bool Inventory<MAX_SIZE, GameObjTy, ItemTy>::empty() const
{
	return m_items.empty();
}

template<unsigned int MAX_SIZE, typename GameObjTy, typename ItemTy>
bool Inventory<MAX_SIZE, GameObjTy, ItemTy>::full() const
{
	return max_size() <= size();
}
