#include <iostream>
#include <string_view>

class Fruit
{
private:
	std::string_view m_name{};
	std::string_view m_colour{};

public:
	Fruit(std::string_view name, std::string_view colour) :m_name{ name }, m_colour{ colour }{}

	std::string_view getName() const { return m_name; }
	std::string_view getColour() const { return m_colour; }
};

class Apple :public Fruit
{
private:
	double m_fiber{};

public:
	Apple(std::string_view name, std::string_view colour, double fiber) 
		:Fruit{ name,colour }, m_fiber{ fiber }{}

	double getFiber() const { return m_fiber; }

	friend std::ostream& operator<<(std::ostream& out, const Apple& apple);
};

class Banana :public Fruit
{
public:
	Banana(std::string_view name, std::string_view colour) :Fruit{ name,colour } {}

	friend std::ostream& operator<<(std::ostream& out, const Banana& banana);
};

std::ostream& operator<<(std::ostream& out, const Apple& apple)
{
	std::cout << "Apple(" << apple.getName() << ", " << apple.getColour() << ", " << apple.getFiber() << ")\n";

	return out;
}

std::ostream& operator<<(std::ostream& out, const Banana& banana)
{
	std::cout << "Banana(" << banana.getName() << ", " << banana.getColour() << ")\n";

	return out;
}

int main()
{
	const Apple a{ "Red delicious", "red", 4.2 };
	std::cout << a << '\n';

	const Banana b{ "Cavendish", "yellow" };
	std::cout << b << '\n';

	return 0;
}