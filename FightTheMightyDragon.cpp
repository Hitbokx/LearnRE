#include <iostream>
#include <string_view>
#include <string>
#include <array>
#include <random>
#include <cassert>

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
		int rNum = monster( mt );

		return Monster{ static_cast<Type>(rNum) };
	}
};

std::string_view inputName( )
{
	std::cout << "Enter your name: ";
	std::string name;
	std::cin >> name;

	std::cout << "Welcome to the game, " << name << "!\n";
	std::cout << '\n';

	return name;
}

char inputChance( )
{
	std::cout << "Run or Fight: ";
	std::string input;
	std::cin >> input;

	if ( input == "Run" || input == "RUN" || input == "run" || input == "R" || input == "r" )
		return 'r';
	else if ( input == "Fight" || input == "FIGHT" || input == "fight" || input == "F" || input == "f" )
		return 'f';
	else
		assert( "Invalid input!" );
}

void attackPlayer( Player& player, Monster& monster );
void attackMonster( Player& player, Monster& monster );

bool fightMonster( char input, Player& player, Monster& monster )
{
	if ( input == 'r' )
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution run{ 0,1 };

		if ( run( mt ) )
		{
			std::cout << "You successfully fled.\n";
			std::cout << '\n';

			return true;
		}
		else
		{
			std::cout << "You failed to flee.\n";
			attackPlayer( player, monster );
			if ( player.isDead( ) )
			{
				std::cout << "You died at level " << player.getLevel( ) << " and with " << player.getGold( ) << " gold.\n";
				return false;
			}
			else
			{
				input = inputChance( );
				fightMonster( input, player, monster );
			}
		}
	}

	if ( input == 'f' )
	{
		attackMonster( player, monster );
		
		if ( monster.isDead() )
		{
			return true;
		}
		if ( player.isDead() )
		{
			return false;
		}
	}
}

void attackPlayer( Player& player, Monster& monster )
{
	player.reduceHealth( monster.getDamage( ) );
	std::cout<<"The "<<monster.getName( ) << " hit you for " << monster.getDamage( ) << " damage.\n";
	std::cout << '\n';
	std::cout << "Now, your health is " << player.getHealth( )<<".\n";
	std::cout << '\n';
}

void attackMonster( Player& player, Monster& monster )
{
	monster.reduceHealth( player.getDamage( ) );
	std::cout << "You hit the " << monster.getName( ) << " for " << player.getDamage( ) << " damage.\n";

	if ( monster.isDead( ) )
	{
		std::cout << "You killed the " << monster.getName( ) << ".\n";
		player.addGold( monster.getGold( ) );
		player.levelUp( );
		std::cout << "You are now 'Level " << player.getLevel( ) << "'.\n";
		std::cout << "You found " << monster.getGold( ) << " gold.\n";
		std::cout << '\n';
	}
	else
	{
		attackPlayer( player, monster );
		if ( player.isDead( ) )
		{
			std::cout << "You died at level " << player.getLevel( ) << " and with " << player.getGold( ) << " gold.\n";
			return;
		}
		else
		{
			char input{ inputChance( ) };
			fightMonster( input, player, monster );
		}
	}
}

int main( )
{
	Player player{ inputName( ) };
	Monster monster{ Monster::getRandomMonster( ) };

	std::cout << "You have encountered a " << monster.getName( ) << ".\n";
	char input{ inputChance( ) };

	while ( true )
	{
		if ( fightMonster( input, player, monster ) )
		{
			if ( player.hasWon() )
			{
				std::cout << "Congrats! You won the game with " << player.getGold( ) << " gold!\n";
				return 0;
			}
			monster = Monster::getRandomMonster( );
			std::cout << "You have encountered a " << monster.getName( ) << ".\n";
			input = inputChance( );
		}
		else
		{
			std::cout << "Too bad you can't take it with you!\n";
			return 0;
		}
	}
}