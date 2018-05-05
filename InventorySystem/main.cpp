#include "DamagePotion.h"
#include "Inventory.h"
#include "HealPotion.h"
#include "Sword.h"

std::ostream& operator<<(std::ostream& out, ItemID const& id)
{
	if (id == ItemID::DAMAGE_POTION)
	{
		out << "ID_DAMAGE_POTION";
	}
	else if (id == ItemID::DEFAULT_ITEM) out << "ID_DEFAULT_ITEM";
	else if (id == ItemID::HEAL_POTION) out << "ID_HEAL_POTION";
	else if (id == ItemID::SWORD) out << "ID_SWORD";
	return out;
}

//Replace temp::GameObject class with the GameObject class used by your game

class Player : public temp::GameObject
{
public:
	Player() : temp::GameObject(200)
	{
		try
		{
			

			m_inventory.emplaceItem<DamagePotion>("Damage Potion I", 50);
			m_inventory.emplaceItem<HealPotion>("Heal Potion I", 70);
			m_inventory.emplaceItem<Sword>("Sword I", 20);

			std::cout << "Inventory contents after adding base items:\n";
			for (auto const& it : m_inventory.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			m_inventory.useItem("Damage Potion I", this);
			m_inventory.useItem("Heal Potion I", this);
			m_inventory.useItem("Sword I");

			std::cout << "Inventory contents after using base items:\n";
			for (auto const& it : m_inventory.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			m_inventory.useItem("Sword I"); // will unequip Sword I

			std::cout << "Inventory contents after unequipping Sword I:\n";
			for (auto const& it : m_inventory.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			chest.emplaceItem<DamagePotion>("CDmgPot", 100);
			chest.emplaceItem<HealPotion>("CHealPot", 200);

			std::cout << "Chest contents after adding base items:\n";
			for (auto const& it : chest.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			m_inventory.merge(chest);

			std::cout << "Chest contents after merging with inventory:\n";
			for (auto const& it : chest.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";
			std::cout << "Inventory contents after merging with chest:\n";
			for (auto const& it : m_inventory.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			chest.emplaceItem<Sword>("CSword", 50);

			std::cout << "Chest contents after adding CSword:\n";
			for (auto const& it : chest.contents()) std::cout << it.second.first ->id() << "\n";
			std::cout << "\n";

			chest.transfer(m_inventory, "CSword");

			std::cout << "Inventory contents after transferring CSword from chest:\n";
			for (auto const& it : m_inventory.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			chest.emplaceItem<Sword>("CSword", 20);

			std::cout << "Chest contents after adding a CSword:\n";
			for (auto const& it : chest.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";

			chest.removeItem("CSword");

			std::cout << "Chest contents after removing a CSword:\n";
			for (auto const& it :chest.contents()) std::cout << it.second.first->id() << "\n";
			std::cout << "\n";
		}
		catch (std::runtime_error e)
		{
			std::cerr << e.what();
		}
	}

private:
	Inventory<200> m_inventory { this };

	Inventory<5> chest { this };
};


struct InvalidItem
{

};

struct InvalidEquippable
{
	void equippable()
	{

	}
};

class TestClass : public temp::GameObject
{
public:
	TestClass()
	{
		try
		{

			Inventory<100> inv { this };

			inv.emplaceItem<DamagePotion>("P", 20);
			inv.addItem<DamagePotion>("P");

			std::cout << inv.getItemCount("P") << '\n';

			inv.useItem("P", this);
			inv.useItem("P", this);

			std::cout << inv.getItemCount("P") << '\n';
		}
		catch (Inventory<100>::Exception e)
		{
			std::cout << e.what() << "\n";
		}
	}
};


int main()
{
	TestClass T;


//	Player p;


//	IItem* base_ptr;

//	Inventory<200> {nullptr};

	//Fails to compile due to traits
//	Inventory<100, temp::GameObject, InvalidItem> {nullptr};
//	Inventory<100, temp::GameObject, InvalidEquippable> {nullptr};

//	base_ptr = new DamagePotion(20);

//	temp::GameObject target { 100 };
/*
	std::cout << "Using Item: \n";
	std::cout << "Name:\t" << base_ptr->name() << "\n";
	std::cout << "ID:\t" << base_ptr->id() << "\n";

	base_ptr->use(&target);

*/


	std::cin.get();
}