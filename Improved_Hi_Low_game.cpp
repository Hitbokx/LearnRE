#include <iostream> 
#include <random>
#include <limits>

bool playAgain();

int generateRandomNumber()
{
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	std::mt19937 mt{ ss };
	std::uniform_int_distribution rNumber{ 1,100 };

	return rNumber(mt);
}

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

bool errorInput()
{
	if (std::cin.fail())
	{
		std::cin.clear();
		ignoreLine();
		std::cout << "Don't waste my time and enter a valid number.\n";
		return true;
	}

	else
	{
		ignoreLine();
		return false;
	}
}

void validateInput()
{
	std::cout << "Let's play a game. I'm thinking of a number. You have 7 tries to guess what it is." << '\n';
	int input{};

	int rNumber{ generateRandomNumber() };
	int count{};

	for (count = 1; count <= 7; ++count)
	{
		do
		{
			std::cout << "Guess #" << count << ": \n";
			std::cin >> input;  
		} 
		while (errorInput());
		
			
		if (input != rNumber)
		{
			if (input < 0 || input > 100)
			{
				std::cout << "Please enter a number between 1 and 100 if you don't want to waste your tries ;) :) \n";
			}

			else if(input > rNumber)
			{
				std::cout << "Your guess is too high. \n";
			}

			else if(input < rNumber)
			{
				std::cout << "Your guess is too low. \n";
			}

		}

		if (input == rNumber)
		{
			std::cout << "Correct! You win! \n";
			std::cout << '\n';
			playAgain();
		}

	}


	if (input != rNumber)
	{
		std::cout << "Sorry, you lose. The correct number was " << rNumber << '\n';
		std::cout << '\n';
		playAgain();
	}
}

bool playAgain()
{
	while (true)
	{
		char input{};
		std::cout << "Would You like to play again(y/n)? ";
		std::cin >> input;
		std::cout << '\n';

		switch (input)
		{
			case 'y':
				validateInput();
				return true;

			case 'n':
				std::cout << "Thank you for playing.\n";
				return false;

			default:
				std::cout << "Don't be oversmart and enter 'y' for 'yes' or 'n' for 'no'.\n";
				std::cout << '\n';
		}
	}
}

int main()
{
	validateInput();
	return 0;
}