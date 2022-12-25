#include <iostream>
#include <string_view>
#include <string>
#include <array>
#include <random>
#include <cassert>

int getRandomNumber( int min, int max )
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution rNum{ min,max };
	return rNum( mt );
}

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

	void increaseHealth( int health ){ m_health += health; }

	void increaseDamage( int damage ){ m_damage += damage; }

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
		int rNum{ getRandomNumber( 0, (static_cast<int>(Type::max_types) - 1) ) };

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
		int run{ getRandomNumber( 0,1 ) };

		if ( run )
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

		// Different types of Potions

		int potion{ getRandomNumber( 0,3 ) };
		if ( potion )
		{
			std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
			char input{};
			std::cin >> input;

			int potionEffect{ getRandomNumber( 1,3 ) };
			if ( input == 'y' )
			{
				switch ( potion )
				{
					case 1:
						{
							switch ( potionEffect )
							{
								case 1:
									{
										player.increaseHealth( 2 );
										std::cout << "Your health has been increased by drinking a 'Health increasing' potion which has a small effect."
											<< "Your health has been increased by " << 2 << " points.\n";

										std::cout << "Now, your health is: " << player.getHealth( ) << ".\n";
										std::cout << '\n';
										break;
									}
								case 2:
									{
										player.increaseHealth( 2 );
										std::cout << "Your health has been increased by drinking a 'Health increasing' potion which has a medium effect."
											<< "Your health has been increased by " << 2 << " points.\n";
										std::cout << "Now, your health is: " << player.getHealth( ) << ".\n";
										std::cout << '\n';
										break;
									}
								case 3:
									{
										player.increaseHealth( 5 );
										std::cout << "Your health has been increased by drinking a 'Health increasing' potion which has a large effect."
											<< "Your health has been increased by " << 5 << " points.\n";
										std::cout << "Now, your health is: " << player.getHealth( ) << ".\n";
										std::cout << '\n';
										break;
									}
							}
							break;
						}
					case 2:
						{
							switch ( potionEffect )
							{
								case 1:
									{
										player.increaseDamage( 2 );
										std::cout << "Your damage has been increased by drinking a 'Strength increasing' potion which has a small effect."
											<< "Your Damage has been increased by " << 2 << " points.\n";
										std::cout << "Now, the damage given by you will be: " << player.getDamage( ) << ".\n";
										std::cout << '\n';
										break;
									}
								case 2:
									{
										player.increaseDamage( 3 );
										std::cout << "Your damage has been increased by drinking a 'Strength increasing' potion which has a medium effect."
											<< "Your damage has been increased by " << 2 << " points.\n";
										std::cout << "Now, the damage given by you will be: " << player.getDamage( ) << ".\n";
										std::cout << '\n';
										break;
									}
								case 3:
									{
										player.increaseDamage( 5 );
										std::cout << "Your damage has been increased by drinking a 'Strength increasing' potion which has a large effect."
											<< "Your damage has been increased by " << 5 << " points.\n";
										std::cout << "Now, the damage given by you will be: " << player.getDamage( ) << ".\n";
										std::cout << '\n';
										break;
									}
							}
							break;
						}
					case 3:
						{
							switch ( potionEffect )
							{
								case 1:
									{
										player.reduceHealth( 1 );
										std::cout << "Your health has been decreased by drinking a 'Health decreasing' poison which has a small effect."
											<< "Your Health has been decreased by " << 2 << " points.\n";
										std::cout << "Now, your health is: " << player.getHealth( ) << ".\n";
										std::cout << '\n';
										break;
									}
								case 2:
									{
										player.reduceHealth( 1 );
										std::cout << "Your health has been decreased by drinking a 'Health decreasing' poison which has a small effect."
											<< "Your Health has been decreased by " << 2 << " points.\n";
										std::cout << "Now, your health is: " << player.getHealth( ) << ".\n";
										std::cout << '\n';
										break;
									}
								case 3:
									{
										player.reduceHealth( 2 );
										std::cout << "Your health has been decreased by drinking a 'Health decreasing' poison which has a small effect."
											<< "Your Health has been decreased by " << 2 << " points.\n";
										std::cout << "Now, your health is: " << player.getHealth( ) << ".\n";
										std::cout << '\n';
										break;
									}
							}
							break;
						}
				}
			}
		}
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