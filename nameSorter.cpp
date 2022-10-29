#include <iostream>
#include <algorithm>
#include <string>

int main()
{
	std::cout << "How many names would you like to enter?(Please follow the consistency of writing the first letter of the name either capital or small) ";
	int length{};
	std::cin >> length;

	auto* names{ new std::string[length]{} };
	for (int i{ 0 }; i < length; ++i)
	{
		std::cout << "Enter name #" << i+1 << ": ";
		std::string name{};
		std::getline(std::cin >> std::ws, name);
		names[i] = name;
	}
	std::cout << '\n';

	std::sort(names, names + length);

	std::cout << "Here is your sorted list:\n";
	for (int i{ 0 }; i < length; ++i)
	{
		std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
	}
	std::cout << '\n';

	delete[] names;

	return 0;
}