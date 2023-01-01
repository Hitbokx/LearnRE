#include <iostream>
#include <stdexcept>
#include <exception>

class Fraction
{
private:
	int m_num{ 0 };
	int m_den{ 1 };

public:
	Fraction( int num, int den ) :m_num{ num }, m_den{ den }
	{
		if ( den <= 0 )
			throw std::exception( "Invalid Denominator" );
	}

	friend std::ostream& operator<<( std::ostream& out, const Fraction& f )
	{
		std::cout << "Fraction is: " << f.m_num << '/' << f.m_den << '\n';
		return out;
	}
};

int main( )
{
	std::cout << "Enter the numerator: ";
	int num{};
	std::cin >> num;

	std::cout << "Enter the denominator: ";
	int den{};
	std::cin >> den;

	try
	{
		std::cout << Fraction{ num, den } << '\n';
	}
	catch ( const std::exception& exception )
	{
		std::cout << exception.what( ) << '\n';
	}
	return 0;
}