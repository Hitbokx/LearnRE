#include <iostream>
#include <numeric> // for std::gcd

class Fraction
{
private:
	int m_numerator{};
	int m_denominator{};

public:
	Fraction(int numerator = 0, int denominator = 1) 
		:m_numerator{ numerator }, m_denominator{ denominator }{reduce(); }

	void reduce()
	{
		int gcd{ std::gcd(m_numerator, m_denominator) };
		if (gcd)
		{
			m_numerator /= gcd;
			m_denominator /= gcd;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);

	friend bool operator==(const Fraction& frac1, const Fraction& frac2);
	friend bool operator!=(const Fraction& frac1, const Fraction& frac2);
	friend bool operator<=(const Fraction& frac1, const Fraction& frac2);
	friend bool operator>=(const Fraction& frac1, const Fraction& frac2);
	friend bool operator<(const Fraction& frac1, const Fraction& frac2);
	friend bool operator>(const Fraction& frac1, const Fraction& frac2);
};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}

bool operator==(const Fraction& frac1, const Fraction& frac2)
{
	return (frac1.m_numerator == frac2.m_numerator && frac1.m_denominator == frac2.m_denominator);
}

bool operator!=(const Fraction& frac1, const Fraction& frac2)
{
	return !(frac1 == frac2);
}

bool operator<(const Fraction& frac1, const Fraction& frac2)
{
	return (frac1.m_numerator * frac2.m_denominator < frac1.m_denominator * frac2.m_numerator);
}

bool operator>(const Fraction& frac1, const Fraction& frac2)
{
	return (frac2 < frac1);
}

bool operator>=(const Fraction& frac1, const Fraction& frac2)
{
	return !(frac2 < frac1);
}

bool operator<=(const Fraction& frac1, const Fraction& frac2)
{
	return !(frac2 > frac1);
}
int main()
{
	Fraction f1{ 3, 2 };
	Fraction f2{ 5, 8 };

	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
	std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
	std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';
	return 0;
}