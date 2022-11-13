#include<iostream>
#include <random>
#include <vector>
#include <cmath>

int start()
{
    std::cout << "Start where? ";
    int start{};
    std::cin >> start;
    return start;
}

int numbersToGenerate()
{
    std::cout << "How many? ";
    int number{};
    std::cin >> number;
    return number;
}

int generateRandomNumber()
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution rNumber{ 2,4 };
     return rNumber(mt);
}

int userInput(int endPoint,int rNumber)
{
    std::cout << "I generated " << endPoint << " square numbers. Do you know what each number is after multiplying it by " << rNumber << "?\n";
    std::cout << "> ";
    int input{};
    std::cin >> input;
    return input;
}

int main()
{
    int startPoint{ start() };
    int endPoint(numbersToGenerate());

    std::vector<int> range(endPoint);
    int rNumber{ generateRandomNumber() };

    for (int element{ 0 }; element < endPoint; ++element)
    {
        range[element] = ((startPoint + element) * (startPoint + element))*rNumber;
    }
   
    int input{ userInput(endPoint, rNumber) };
    int maxWrongAnswer{ 4 };

    while (true)
    {
        auto found{ std::find(range.begin(),range.end(),input) };

        if (found == range.end())
        {
            const auto closest
            { std::min_element(range.begin(), range.end(),
                 [=](int a,int b)
                 {
                    return(std::abs(a - input) < std::abs(b - input));
                 }
            ) };

            if (std::abs(*closest - input) <= maxWrongAnswer)
            {
                std::cout << input << " is wrong!";
                std::cout << " Try " << *closest << " next time.\n";
            }
            else
                std::cout << input << " is wrong!\n";
            
           break;
        }
        else
        {
            endPoint -= 1;
            std::cout << "Nice! " << endPoint << " number(s) left.\n";
            range.erase(found);

            if (endPoint == 0)
            {
                std::cout << "Nice! You found all numbers, good job!\n";
                break;
            }
            
            std::cout << "> ";
            std::cin >> input;
        }
    }
    return 0;
}