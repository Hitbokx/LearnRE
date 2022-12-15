#include <iostream>
#include <map> // std::map
#include <string>

int main()
{
	// std::map can be initialized
	std::map<std::string, char> grades
	{
		{ "Joe", 'A' },
		{ "Frank", 'B' }
	};

	// and assigned
	grades["Susan"] = 'C';
	grades["Tom"] = 'D';

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

	return 0;
}