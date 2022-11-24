#include <iostream>
#include <string>
#include <string_view>

class Ball
{
private:
	std::string	m_colour{};
	double m_radius{};
public:

	Ball(double radius)
	{
		m_colour = "black";
		m_radius = radius;
	}

	Ball(std::string_view colour = "black", double radius = 10.0)
	{
		m_colour = colour;
		m_radius = radius;
	}

	void print()
	{
		std::cout << "Colour: " << m_colour << ", radius: " << m_radius << '\n';
	}
};

int main()
{
	Ball def{};
	def.print();

	Ball blue{ "blue" };
	blue.print();

	Ball twenty{ 20.0 };
	twenty.print();

	Ball blueTwenty{ "blue", 20.0 };
	blueTwenty.print();

	return 0;
}