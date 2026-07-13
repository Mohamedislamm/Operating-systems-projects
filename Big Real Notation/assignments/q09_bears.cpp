// File: q09_bears.cpp
// Purpose: Recursive bears puzzle solver.
// Author: mohammed gamal abd el nasser Atteya (20221119)

#include <iostream>

bool bears(int n)
{
    if(n==42)
    {
        return true;
    }
    if(n %2==0 && bears(n/2))
    {
        return true;
    }
    int lastNumber=n % 10;
    int BeforeLast=(n % 100)/10;
    int newN=n-(lastNumber * BeforeLast);

    if ((n%3==0 || n%4==0) && newN>0 && bears(newN))
    {
        return true;
    }
    if (n%5==0 && bears(n-42))
    {
        return true;
    }
    return false;
}

int main() {
    int n;
    std::cout<<"enter bears number: ";
    std::cin>>n;
    if (bears(n))
    {
        std::cout <<"True"<<std::endl;
    } else {
        std::cout<<"False"<<std::endl;
    }
}
