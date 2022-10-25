#include <iostream>

struct Fraction
{
	int numerator{};
	int denominator{};
};

Fraction getFraction()
{
	Fraction fraction{};

	static int x = 1;
	if (x == 1) 
	{
		std::cout << "Enter a value for the numerator: ";
		std::cin >> fraction.numerator;

		std::cout << "Enter a value for the numerator: ";
		std::cin >> fraction.denominator;

		x = 0;
	}

	else
	{
		std::cout << "\nEnter another value for the numerator: ";
		std::cin >> fraction.numerator;

		std::cout << "Enter another value for the numerator: ";
		std::cin >> fraction.denominator;

		x = 1;
	}

	return fraction;
}

Fraction multiplyFraction(const Fraction& fraction1, const Fraction& fraction2)
{
	return { fraction1.numerator * fraction2.numerator, fraction1.denominator * fraction2.denominator };
}

void printFraction(const Fraction& fraction)
{
	std::cout << "\nYour fractions multiplied together: " << fraction.numerator << '/' << fraction.denominator << '\n';
}

int main()
{
	Fraction fraction1{ getFraction() };
	Fraction fraction2{ getFraction() };

	printFraction(multiplyFraction(fraction1, fraction2));

	return 0;
}