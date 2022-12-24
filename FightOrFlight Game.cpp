#include <iostream>
#include <string_view>
#include <array>
#include <random>

class Creature
{
protected:
	std::string_view m_name{};
	char m_symbol{};
	int m_health{};
	int m_damage{};
	int m_gold{};

public:
	Creature( std::string_view name, char symbol, int health, int damage, int gold )
		:m_name{ name }, m_symbol{ symbol }, m_health{ health }, m_damage{ damage }, m_gold{ gold }{}

	std::string_view getName( ) const{ return m_name; }
	char getSymbol( ) const{ return m_symbol; }
	int getHealth( ) const{ return m_health; }
	int getDamage( ) const{ return m_damage; }
	int getGold( ) const{ return m_gold; }

	void reduceHealth( int damage ){ m_health -= damage; }

	bool isDead( ){ return{ m_health <= 0 }; }

	void addGold( int gold ){ m_gold += gold; }
};

class Player :public Creature
{
private:
	int m_level{ 1 };

public:
	Player( std::string_view name )
		:Creature{ name, '@',  10, 1, 0 }{}

	void levelUp( )
	{
		++m_level;
		++m_damage;
	}

	int getLevel( ) const { return m_level; }

	bool hasWon( ){ return m_level >= 20; }
};

class Monster :public Creature
{
public:
	enum class Type
	{
		dragon,
		orc,
		slime,

		max_types,
	};

private:
	static const Creature& defaultCreature( Type type )
	{
		static const std::array < Creature, static_cast<std::size_t>(Type::max_types)> monsterData
		{
			{
			{"Dragon", 'D', 20, 4, 100},
			{"Orc", 'O', 4, 2, 25},
			{"Slime", 'S', 1, 1, 10},
			}
		};
		return monsterData.at( static_cast<std::size_t>(type) );
	}

public:
	Monster( Type type ) :Creature{ defaultCreature( type ) }{}

	static Monster getRandomMonster( )
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution monster{ 0, (static_cast<int>(Type::max_types) - 1) };

		return Monster{ static_cast<Type>(monster( mt )) };
	}
};

std::string_view inputName( )
{
	std::cout << "Enter your name: ";
	std::string name;
	std::cin >> name;

	std::cout << "Welcome, " << name << '\n';

	return name;
}

int main( )
{

	for ( int i{ 0 }; i < 30; ++i )
	{
		Monster m{ Monster::getRandomMonster( ) };
		std::cout << "A " << m.getName( ) << " (" << m.getSymbol( ) << ") was created.\n";
	}

	return 0;
}