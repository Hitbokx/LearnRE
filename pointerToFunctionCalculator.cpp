#include <iostream>
#include <limits>
#include <functional>
#include <cassert>

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getInteger()
{
	while (true)
	{
		static bool s_bool{ true };
		if (s_bool) 
		{
			std::cout << "Enter an integer: ";
			int input{};
			std::cin >> input;

			if (!std::cin)
			{
				std::cin.clear();
				ignoreLine();
				std::cout << "Oops you entered an invalid input. Please try again.\n";
			}

			else
			{
				ignoreLine();
				s_bool = false;
				return input;
			}
		}

		else
		{
			std::cout << "Enter another integer: ";
			int input{};
			std::cin >> input;

			if (!std::cin)
			{
				std::cin.clear();
				ignoreLine();
				std::cout << "Oops you entered an invalid input. Please try again.\n";
			}

			else
			{
				ignoreLine();
				s_bool = true;
				return input;
			}
		}
	}
}

char getOperator()
{
	while (true)
	{
		std::cout << "Enter an operator( +, -, *, / ):";
		char operation{};
		std::cin >> operation;
		ignoreLine();
		switch (operation)
		{
			case '+':
			case '-':
			case '*':
			case '/':
				return operation;
			default:
				std::cout << "Oops you entered an invalid input. Please try again.\n";
		}
	}
}

int add(int x, int y)
{
	return x + y;
}

int subtract(int x, int y)
{
	return x - y;
}

int multiply(int x, int y)
{
	return x * y;
}

int divide(int x, int y)
{
	return x / y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char op)
{
	switch (op)
	{
		case '+':
			return add;
		case '-':
			return subtract;
		case '*':
			return multiply;
		case '/':
			return divide;
		default:
			return nullptr;
	}
}

int main()
{
	int x{ getInteger() };
	char op{ getOperator() };
	int y{ getInteger() };

	ArithmeticFunction fncPtr{ getArithmeticFunction(op) };
	if (fncPtr)
	{
		std::cout << x <<' '<<op<<' '<<y<<' '<<'='<<' '<< fncPtr(x, y);
	}
	else
	{
		assert(false && "Returned a null pointer\n");
	}

	return 0;
}