#include <iostream>
#include <cassert>
#include <iterator>

class IntArray
{
private:
	int m_size{};
	int* m_arr{ nullptr };

public:

	IntArray(int size) :m_size{ size } { m_arr = new int[m_size]; }

	//~IntArray() { delete[] m_arr; }

	int& operator[] (int index);
	IntArray& operator=(const IntArray& array);
	friend std::ostream& operator<<(std::ostream& out, const IntArray& arr);
};

int& IntArray::operator[] (int index)
{
	assert(index >= 0 && index < m_size);

	return m_arr[index];
}

IntArray& IntArray::operator=(const IntArray& array)
{
	if (this == &array)
		return *this;

	if (m_arr) delete[] m_arr;
	m_size = array.m_size;

	m_arr = new int[array.m_size];

	for (int i{ 0 }; i < array.m_size; ++i)
		m_arr[i] = array.m_arr[i];

	return *this;
}

std::ostream& operator<<(std::ostream& out, const IntArray& array)
{
	for (int i{ 0 }; i < array.m_size; ++i)
		std::cout << array.m_arr[i];

	return out;
}

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };
	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	std::cout << b << '\n';

	return 0;
}