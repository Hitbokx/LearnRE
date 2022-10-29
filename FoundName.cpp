#include <iostream>
#include <string_view>

int main()
{
	std::string_view names[]{"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };

	std::cout << "Enter a name: ";
	std::string input{};
	std::cin >> input;

	bool found{ false };

	for (std::string_view name : names)
	{
		if (input == name)
		{
			found = true;
			break;
		}
	}

	if(found)
		std::cout << input << " was found.";
	else
		std::cout << input << " was not found.";
	
	return 0;
}