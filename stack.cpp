#include <iostream>
#include <array>
#include <cassert>

class Stack
{
private:
    using Array = std::array<int, 10>;
    int stackSize{0};
    Array array{};
   //int full{ 10 };
public:
    void reset()
    {
        stackSize = 0;
    }

    bool push(int val)
    {
        if (stackSize == array.size())
            return false;
        else
        {
            array[stackSize++] = val;
            return true;
        }
    }

    Array pop()
    {
        if (stackSize == 0)
            assert("value not found");

         array[stackSize--] = 0;
         return array;
    }

    void print()
    {
        std::cout << "( ";
        for (int i{ 0 }; i < stackSize; ++i)
        {
            std::cout << array[i] << ' ';
        }
        std::cout << ")\n";
    }
    
};

int main()
{
    Stack stack;
    stack.print();

    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.push(6);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();

    stack.print();


    return 0;
}