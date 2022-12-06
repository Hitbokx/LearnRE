#include <iostream>
#include <string>
#include <ctime> 
#include <cstdlib>
#include <array>

class Monster
{
public:
	enum class Type
	{
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,

		max_monster_types,
	};

private:
	Type m_type{};
	std::string m_name{};
	std::string m_roar{};
	int m_hitPoints{};

public:
	Monster(Monster::Type type, std::string name, std::string roar, int hitPoints)
		: m_type{type},m_name{name},m_roar{roar},m_hitPoints{hitPoints}{}

	std::string_view getTypeString(Type type) const
	{
		using enum Type;
		switch (type)
		{
			case dragon:	return "dragon";
			case goblin:	return "goblin";
			case ogre:		return "ogre";
			case orc:		return "orc";
			case skeleton:	return "skeleton";
			case troll:		return "troll";
			case vampire:	return "vampire";
			case zombie:	return "zombie";
			default:		return "??????";
		}
	}

	void print()
	{
		std::cout << m_name << " the " << getTypeString(m_type) << " has " << m_hitPoints << " points and " << m_roar << '\n';
	}

};

class MonsterGenerator
{
public:
	static int getRandomNumber(int min, int max)
	{
		static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  
		return min+static_cast<int>((std::rand() * fraction) * (max - min + 1) + min);
	}

	static Monster generateMonster()
	{
		Monster::Type type{ static_cast<Monster::Type>(getRandomNumber(0,static_cast<int>(Monster::Type::max_monster_types) - 1)) };
		int hitPoints{ getRandomNumber(1,100) };

		static constexpr std::array s_names{ "Gauri","Nemo","Axat","Kanchan","Zimba","Skylar" };
		static constexpr std::array s_roars{ "Roars","Screams","Groans","Grunts","Whines","Moans" };
		std::string name{ s_names[getRandomNumber(0,5)] };

		std::string roars{ s_roars[getRandomNumber(0,5)] };

		return Monster(type, name, roars, hitPoints);
	}
};

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); 
	std::rand(); 

	Monster m{ MonsterGenerator::generateMonster() };
	m.print();
	
	return 0;
}