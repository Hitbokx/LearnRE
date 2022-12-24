#include <iostream>
#include <string>
#include <string_view>

class Fruit
{
private:
	std::string_view m_name{};
	std::string_view m_colour{};

public:
	Fruit(std::string_view name, std::string_view colour ):m_name{name},m_colour{colour}{}

	std::string_view getName( ) const { return m_name; }
	std::string_view getColour( ) const { return m_colour; }
};

class Apple :public Fruit
{
protected:
	Apple( std::string_view name, std::string_view colour ) :Fruit{ name, colour }{}
public:
	Apple( std::string_view colour = "red" ) :Fruit{ "apple", colour}{}
};

class Banana :public Fruit
{
public:
	Banana( std::string_view colour = "yellow" ) :Fruit{ "banana", colour }{}
};

class GrannySmith :public Apple
{
public:
	GrannySmith( ):Apple{"granny smith apple", "green"}{}
};

int main( )
{
	Apple a{ "red" };
	Banana b{};
	GrannySmith c;

	std::cout << "My " << a.getName( ) << " is " << a.getColour( ) << ".\n";
	std::cout << "My " << b.getName( ) << " is " << b.getColour( ) << ".\n";
	std::cout << "My " << c.getName( ) << " is " << c.getColour( ) << ".\n";

	return 0;
}