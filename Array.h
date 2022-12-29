#pragma once

#include <cassert> // for assert()
#include <iostream>

template<typename T>
class Array // value container, array of integers, similar to std::vector<int>
{
private:
	int m_length{};
	T* m_data{};

	void deepCopy(const Array& a) // to ensure use only by members
	{
		reallocate(a.getLength());

		for (int index{ 0 }; index < m_length; ++index)
			m_data[index] = a.m_data[index];
	}

public:
	Array() = default;

	Array(int length) :m_length{ length }
	{
		assert(length >= 0);

		if (length > 0)
			m_data = new T[length] {};
	}

	Array(const Array& a)
	{
		deepCopy(a);
	}

	//Array(const Array&) = delete;

	~Array()
	{
		delete[] m_data;
	}

	void erase()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	Array& operator=(std::initializer_list<T> list)
	{
		// deepCopy(list); 1st option
		int length{ static_cast<int>(list.size()) };

		if (length != m_length) // 2nd option
		{
			delete[] m_data;

			m_length = length;
			m_data = new T[length];
		}
		int count{ 0 };
		for (auto element : list)
		{
			m_data[count] = element;
			++count;
		}
		return *this;
	}

	//Array& operator=(const Array& list) = delete;

	int getLength() const { return m_length; }

	void reallocate(int newLength)
	{
		erase();
		if (newLength <= 0)
			return;

		m_data = new T[newLength];
		m_length = newLength;
	}

	void resize(int newLength)
	{
		if (newLength == m_length)
			return;

		if (newLength <= 0)
		{
			erase();
			return;
		}

		T* data{ new T[newLength] };

		if (m_length > 0)
		{
			int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

			for (int index{ 0 }; index < elementsToCopy; ++index)
				data[index] = m_data[index];
		}

		delete[] m_data;

		m_data = data;
		m_length = newLength;
	}

	Array& operator=(const Array& a)
	{
		if (&a == this)
			return *this;

		deepCopy(a);

		return *this;
	}

	void insertBefore(int value, int index)
	{
		assert(index >= 0 && index <= m_length);

		T* data{ new T[m_length + 1] };

		for (int before{ 0 }; before < index; ++before)
			data[before] = m_data[before];

		data[index] = value;

		data[index] = value;

		for (int after{ index }; after < m_length; ++after)
			data[after + 1] = m_data[after];

		delete[] m_data;
		m_data = data;
		++m_length;
	}

	void remove(int index)
	{
		assert(index >= 0 && index < m_length);

		if (m_length == 1)
		{
			erase();
			return;
		}

		T* data{ new T[m_length - 1] };

		for (int before{ 0 }; before < index; ++before)
			data[before] = m_data[before];

		for (int after{ index + 1 }; after < m_length; ++after)
			data[after - 1] = m_data[after];

		delete[] m_data;
		m_data = data;
		--m_length;
	}

	void insertAtBeginning(int value) { insertBefore(value, 0); }
	void insertAtEnd(int value) { insertBefore(value, m_length); }

	void print()
	{
		for (int i{ 0 }; i < 10; ++i)
		{
			std::cout << (*this)[i] << ' ';
		}
		std::cout << '\n';
		std::cout << '\n';
	}
};