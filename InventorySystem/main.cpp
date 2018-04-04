#include "DamagePotion.h"
#include "Inventory.h"
#include "HealPotion.h"

std::ostream& operator<<(std::ostream& out, ItemID const& id)
{
	if (id == ItemID::DAMAGE_POTION)
	{
		out << "ID_DAMAGE_POTION";
	}
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
			if (m_inventory.getOwner() == nullptr)
			{
				std::cout << "Owner was nullptr, setting to this...\n";
				m_inventory.setOwner(this);
			}

			m_inventory.addItem<DamagePotion>("Damage Potion I", 50);
			m_inventory.addItem<HealPotion>("Heal Potion I", 70);

			m_inventory.useItem("Damage Potion I", this);
			m_inventory.useItem("Heal Potion I", this);
		}
		catch (std::runtime_error e)
		{
			std::cerr << e.what();
		}
	}

private:
	Inventory<200> m_inventory { this };
};

int main()
{

	Player p;

	IItem* base_ptr;

	base_ptr = new DamagePotion(20);

	temp::GameObject target { 100 };

	std::cout << "Using Item: \n";
	std::cout << "Name:\t" << base_ptr->name() << "\n";
	std::cout << "ID:\t" << base_ptr->id() << "\n";

	base_ptr->use(&target);



	std::cin.get();
}