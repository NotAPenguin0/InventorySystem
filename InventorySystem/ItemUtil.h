#pragma once

#include "ItemID.h"
#include <string>
#include <type_traits>

class IItem;
class DamagePotion;
class HealPotion;
class Sword;

template<ItemID ID>
struct ItemType
{
	using type = IItem;
};

template<>
struct ItemType<ItemID::DAMAGE_POTION>
{
	using type = DamagePotion;
};

template<>
struct ItemType<ItemID::HEAL_POTION>
{
	using type = HealPotion;
};

template<>
struct ItemType<ItemID::SWORD>
{
	using type = Sword;
};

inline std::string ItemName(ItemID id)
{
	if (id == ItemID::DEFAULT_ITEM) return "Default Item";
	if (id == ItemID::SWORD) return "Sword";
	if (id == ItemID::DAMAGE_POTION) return "Damage Potion";
	if (id == ItemID::HEAL_POTION) return "Healing Potion";
}

template<typename ItemT>
inline ItemID ItemId()
{
	if constexpr(std::is_same_v<ItemT, IItem>) return ItemID::DEFAULT_ITEM;
	if constexpr(std::is_same_v<ItemT, DamagePotion>) return ItemID::DAMAGE_POTION;
	if constexpr(std::is_same_v<ItemT, HealPotion>) return ItemID::HEAL_POTION;
	if constexpr(std::is_same_v<ItemT, Sword>) return ItemID::SWORD;
	else return ItemID::UNKNOWN_ITEM;
}