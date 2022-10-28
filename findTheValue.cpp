#include <iostream>
#include <iterator>

int* findValue(int* arr1, int* arr2, int value)
{
    for (arr1; arr1 < arr2; ++arr1)
    {
        if (*(arr1) == 20)
        {
            return arr1;
        }

    }
}

int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };

    // Search for the first element with value 20.
    int* found{ findValue(std::begin(arr), std::end(arr), 20) };

    // If an element with value 20 was found, print it.
    if (found != std::end(arr))
    {
        std::cout << *found << '\n';
    }

    return 0;
}