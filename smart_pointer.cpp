#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

class Person
{
private:
	std::string m_name;
	std::weak_ptr<Person> m_partner{};

public:

	Person( std::string_view name ) :m_name{ name }{ std::cout << m_name << " created\n"; }
	~Person( ){ std::cout << m_name << " destroyed\n"; }

	friend bool partnerUp( std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2 )
	{
		if ( !p1 || !p2 )
			return false;

		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

		return true;
	}
	const std::shared_ptr<Person> getPartner( ) const { return m_partner.lock( ); }
	const std::string& getName( ) const{ return m_name; }
};

int main( )
{
	auto gauri{ std::make_shared<Person>( "Gauri" ) };
	auto asmi{ std::make_shared<Person>( "Asmi" ) };

	partnerUp( gauri, asmi );

	auto partner{ gauri->getPartner( ) };
	std::cout << gauri->getName( ) << "'s partner is: " << partner->getName( ) << '\n';

	return 0;
}