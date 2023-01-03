#include <iostream>

template <typename T>
class Auto_ptr1
{
private:
	T* m_ptr{};

public:
	Auto_ptr1( T* ptr = nullptr ) :m_ptr{ ptr }{}

	~Auto_ptr1( ){ delete m_ptr; }

	Auto_ptr1( Auto_ptr1& a )
	{
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
	}

	Auto_ptr1& operator=( Auto_ptr1& a ) // using move semantics, so that we don't end up with duplicate copies of pointer 
	{                                    // and everyting gets cleaned up
		if ( this == &a )
			return *this;

		delete m_ptr;

		m_ptr = a.m_ptr;
		a.m_ptr = nullptr; // make sure the source no longer points to the same address 

		return *this;
	}

	T& operator*( ) const { return *m_ptr; }
	T* operator->( ) const { return m_ptr; }

	bool isNull( ) const { return m_ptr == nullptr; }

};

class Resource
{
public:
	Resource( ){ std::cout << "Resource acquired\n"; }
	~Resource( ){ std::cout << "Resource destroyed\n"; }

	void sayHi( ){ std::cout << "Hi!\n"; }
};

void someFunction( )
{
	Auto_ptr1<Resource> ptr{ new Resource{} };

	int x{};
	std::cout << "Enter an integer: ";
	std::cin >> x;
	if ( x == 0 )
		return;

	ptr->sayHi( );
}

int main( )
{
	Auto_ptr1<Resource> res1{ new Resource{} };
	Auto_ptr1<Resource> res2{};
	std::cout << "res1 is " << (res1.isNull( ) ? "null\n" : "non-null\n");
	std::cout << "res2 is " << (res2.isNull( ) ? "null\n" : "non-null\n");

	res2 = res1;
	std::cout << "Owenership transferred\n";

	std::cout << "res1 is " << (res1.isNull( ) ? "null\n" : "non-null\n");
	std::cout << "res2 is " << (res2.isNull( ) ? "null\n" : "non-null\n");

	return 0;
}