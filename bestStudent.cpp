#include <iostream>
#include <array>
#include <algorithm>
#include <string>

struct Student
{
    std::string name{};
    int points{};
};

int main()
{
    std::array<Student, 8> arr
    {
        { 
            { "Albert", 3 },
            { "Ben", 5 },
            { "Christine", 2 },
            { "Dan", 8 }, // Dan has the most points (8).
            { "Enchilada", 4 },
            { "Francis", 1 },
            { "Greg", 3 },
            { "Hagrid", 5 } 
        }
    };

   const auto mostPoints{ std::max_element(arr.begin(), arr.end(),
                                [](const auto& a, const auto& b)
                                {
                                    return (a.points) < (b.points);
                                }
    ) };
    std::cout << mostPoints->name<<" is the best student.";


	return 0;
}