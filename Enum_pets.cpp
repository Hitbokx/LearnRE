#include <iostream>

enum Pet
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

std::istream& operator>> (std::istream& in, Pet& pet)
{
    int input{};
    in >> input; 

    pet = static_cast<Pet>(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, Pet& pet)
{
    switch (pet)
    {
        case cat: 
            out<< "cat"; 
            break;
        case dog:
            out << "dog";
            break;
        case pig:
            out << "pig";
            break;
        case whale:
            out << "whale";
            break;
        default:
            out << "???";
    }
    return out;
}

int main()
{
    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    Pet pet{};
    std::cin >> pet; 
    std::cout << pet << '\n'; 

    return 0;
}