#pragma once // just #include and use PRNG{}(min, max)
#include <random>

class PRNG
{
public:
	PRNG( ) = default;

	const int& operator()( int min, int max )
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution rNum{ min,max };
		return rNum( mt );
	}
};