// File: q06a_binary.cpp
// Purpose: Convert a positive number to binary recursively.
// Author: mohammed gamal abd el nasser Atteya (20221119)

#include <iostream>

void BinaryNumber(int num)
{
    if (num > 0)
    {
        BinaryNumber(num/2);
        std::cout<<num % 2;
    } else if (num== 0)
    {
        std::cout<<0;
    }
    else
        std::cout<<"wrong input only +ve numbers are allowed"<<std::endl;
}

int main() {
    int num;
    std::cout<<"enter a number to transform into binary : ";
    std::cin>>num;
    BinaryNumber(num);
}
