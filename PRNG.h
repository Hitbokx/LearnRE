#pragma once // just #include and use PRNG{}(min, max)
#include <random>
#include <chrono>

class PRNG
{
private:
	int64_t seedTime{ std::chrono::steady_clock::now( ).time_since_epoch( ).count() };
	int64_t seedRand{ std::random_device{}() };
public:
	PRNG( ) = default;

	const int& operator()( int min, int max )
	{
		std::mt19937 mt{ seedRand };
		std::uniform_int_distribution rNum{ min,max };
		return rNum( mt );
	}
};