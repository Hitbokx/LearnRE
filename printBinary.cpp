#include <iostream>

int getInput()
{
	std::cout << "Please enter a positive integer: ";
	int input{};
	std::cin >> input;

	return input;
}

void convert(int num)
{
	int uNumBit{ num % 2 };

	if (num > 1)
		convert(num / 2);

	if (num < 0)
	{
		int uNum{ num  };
		
		convert( uNum / 2);

		uNumBit = (-(uNum) % 2);

		if (uNumBit == 0)
			uNumBit = 1;

		if (uNumBit == 1)
			uNumBit = 0;
	}

	std::cout <<uNumBit;
}

int main()
{
	convert(-2);

	/*while (true)
	{
		int input{ getInput() };
		std::cout << "The binary representation of " << input << " is: ";
		
		std::cout << '\n';
		std::cout << "Do you want to play again?('y' or 'n') ";
		char ch{};
		std::cin >> ch;

		if (ch == 'n')
			break;
		std::cout << '\n';
	}
	std::cout << "Thank you for playing.";
	std::cout << '\n';
	*/

	return 0;
}