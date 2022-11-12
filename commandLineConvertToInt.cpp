#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		if (argv[0])
			std::cout << "Usage: " << argv[0] << " <number>" << '\n';
		else
			std::cout << "Usage: <program name> <number>" << '\n';

		return 1;
	}

	std::stringstream convert{ argv[1] };  //set up a std::stringstream variable named convert i.e. initialized with the input from argv[1]

	int myInt{};
	if (!(convert >> myInt)) //do the conversion 
		myInt = 0;	// if conversion fails, set myint to a default value

	//std::stringstream works much like std::cin. 
	//In this case, we’re initializing it with the value of argv[1], so that we can use operator>> to extract the value to an integer variable (the same as we would with std::cin).

	std::cout << "Got integer: " << myInt << '\n';

	return 0;
}