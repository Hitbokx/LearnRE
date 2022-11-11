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
	if (num > 1)
	{
		convert(num / 2);
	}
		
	std::cout << num % 2;
}

int main()
{
	while (true)
	{
		int input{ getInput() };
		std::cout << "The binary representation of " << input << " is: ";
		convert(input);
		std::cout << '\n';
		std::cout << "Do you want to play again?('y' or 'n') ";
		char ch{};
		std::cin >> ch;

		if (ch == 'n')
			break;
		std::cout << '\n';
	}
	
	return 0;
}