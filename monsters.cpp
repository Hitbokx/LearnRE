#include <iostream>

enum class Monster_type
{
	ogre,
	dragon,
	orc,
	spider,
	slime,
};

struct Monster
{
	Monster_type monsters{};
	std::string_view name{};
	int health{};
};

std::ostream& operator<<(std::ostream& out, Monster_type monsters)
{
	using enum Monster_type;

	switch (monsters)
	{
		case ogre:
			out << "Ogre";
			break;
		case dragon:
			out << "Dragon";
			break;
		case spider:
			out <<"Spider";
			break;
		case orc:
			out << "Orc";
			break;
		case slime:
			out << "Slime";
			break;
	}
	return out;
}

void printMonster(Monster monster)
{
	Monster_type monster_type{};
	std::cout << "This " << monster_type <<" is named " << monster.name << " and has " << monster.health << " health.\n ";
}
int main()
{
	using enum Monster_type;

	Monster monster1{ogre,"Trog",145};
	Monster monster2{slime,"Blurp",23 };


	printMonster(monster1);
	printMonster(monster2);

	return 0;
}