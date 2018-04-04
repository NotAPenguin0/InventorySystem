#include "DamagePotion.h"

std::ostream& operator<<(std::ostream& out, ItemID const& id)
{
	if (id == ItemID::DAMAGE_POTION)
	{
		out << "ID_DAMAGE_POTION";
	}
	return out;
}

//Replace temp::GameObject class with the GameObject class used by your game

int main()
{

	IItem* base_ptr;

	base_ptr = new DamagePotion(20);

	temp::GameObject target { 100 };

	std::cout << "Using Item: \n";
	std::cout << "Name:\t" << base_ptr->name() << "\n";
	std::cout << "ID:\t" << base_ptr->id() << "\n";

	base_ptr->use(&target);

	std::cin.get();
}