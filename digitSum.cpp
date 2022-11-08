#include <iostream>
#include <vector>

int digitSum(int n)
{
    if (n == 0)
        return 0;

    return digitSum(n / 10) + (n % 10);
}

int main()
{
    std::cout << digitSum(93427);
    return 0;
}