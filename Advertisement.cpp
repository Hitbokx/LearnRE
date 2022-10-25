#include <iostream>

struct Advertisement
{
	int numberOfAddsShown{};
	double percentageOfAddsClicked{};
	double moneyEarnedForEach{};
};

Advertisement getAdd()
{
	Advertisement add;
	std::cout << "Please enter the Number of adds shown: ";
	std::cin >> add.numberOfAddsShown;

	std::cout << "Please enter the  percentage of adds clicked: ";
	double percentageOfAddsClicked{};
	std::cin >> add.percentageOfAddsClicked;

	std::cout << "Please enter the money earned for each advertisement: ";
	int moneyEarnedForEach{};
	std::cin >> add.moneyEarnedForEach;

	return add;
}

void printAdvertisement(const Advertisement& add)
{
	auto totalMoney{ add.numberOfAddsShown * (add.percentageOfAddsClicked / 100) * add.moneyEarnedForEach };
	std::cout << "Money Earnd that day: $" << totalMoney << '\n';
}

int main()
{
	Advertisement add{getAdd()};
		 
	printAdvertisement(add);

	return 0;
}