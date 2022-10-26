#include <iostream>
#include <iterator>

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getInput()
{
	std::cout << "Enter a number between 1 and 9: ";
	int input{};
	std::cin >> input;

	if (!std::cin)
	{
		std::cin.clear();
		ignoreLine();
		std::cout << "Enter a number between 1 and 9: ";
		std::cin >> input;
	}
	else
	{
		ignoreLine();
		return input;
	}

}

void printArray(int input)
{
	constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
	int maxNumber{ 0 };
	for (int i{ 0 }; i < (sizeof(array) / sizeof(array[0])); ++i)
	{
		if (array[i] == input)
		{
			std::cout << "The number " << input << " has index " << i;
			std::cout << '\n';
		}
	}
}
int main()
{
	constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };

	int input{ getInput() };

	for (int i{ 0 }; i < (sizeof(array) / sizeof(array[0])); ++i)
	{
		std::cout << array[i] << ' ';
	}
	std::cout << '\n';

	printArray(input);


	return 0;
}