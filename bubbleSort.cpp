#include<iostream>
#include<iterator>

int main()
{
	int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
	int length{ std::ssize(array) };

	for (int i{ 0 }; i < length - 1; ++i)
	{
		int sortedNumber{ length - 1 };
		for (int currentIndex{ 0 }; currentIndex < sortedNumber; ++currentIndex)
		{
			if (array[currentIndex] > array[currentIndex + 1])
			{
				std::swap(array[currentIndex], array[currentIndex + 1]);
			}

		}
		--sortedNumber;
		
	}

	for (int index{ 0 }; index < length; ++index)
	{
		std::cout << array[index] << ' ';
	}

	std::cout << '\n';
	return 0;
}
