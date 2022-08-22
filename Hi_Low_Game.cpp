#include <iostream> 
#include <random>

void userInput2();

int generateRandomNumber()
{
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	std::mt19937 mt{ ss };
	std::uniform_int_distribution rNumber{ 1,100 };

	return rNumber(mt);
}

void userInput()
{
	std::cout << "Let's play a game. I'm thinking of a number. You have 7 tries to guess what it is." << '\n';

	int rNumber{ generateRandomNumber() };

	int input{};
	int count{};

	for (int count{ 1 }; count <= 7; ++count)
	{
		if (count != rNumber)
		{
			std::cout << "Guess #" << count << ": \n";
			std::cin >> input;

			if (input < 0 || input > 100)
			{
				std::cout << "Please enter a number between 1 and 100 if you don't want to waste your tries ;) :) \n";
			}

			if (input > rNumber)
			{
				std::cout << "Your guess is too high. \n";
			}

			if (input < rNumber)
			{
				std::cout << "Your guess is too low. \n";
			}
		}


	}

	if (count != rNumber)
	{
		std::cout << "Sorry, you lose. The correct number was " << rNumber << '\n';
	}

	if (input == rNumber)
	{
		std::cout << "Correct! You win! \n";
		std::cout << '\n';
	}


	/*

	int count = 1;
	do
	{
		std::cout << "Guess #" << count << ": \n";
		std::cin >> input;

		if (input > rNumber)
		{
			std::cout << "Your guess is too high. \n";
		}

		if (input < rNumber)
		{
			std::cout << "Your guess is too low. \n";
		}

		++count;

	} while (input != rNumber);


	std::cout << "Guess #" << count << ": \n";
	std::cout << "Correct! You win!";
	std::cout << '\n';

	*/





	userInput2();

}

void userInput2()
{
	std::cout << "Would you like to play again (y/n)?";
	char input{};
	std::cin >> input;

	switch (input)
	{
		case 'y':
			userInput();
			return;
		case 'n':
			std::cout << "Thank you for playing.\n";
			return;
		default:
			std::cout << "Would you like to play again (y/n)?";
			std::cin >> input;
	}
}


int main()
{
	userInput();
	return 0;
}