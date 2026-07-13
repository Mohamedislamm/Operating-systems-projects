// File: q06b_binary_strings.cpp
// Purpose: Generate all binary strings of length k with a given prefix.
// Author: mohammed gamal abd el nasser Atteya (20221119)

#include <iostream>
#include <string>
using std::string;

void numbers(string Prefix, int k) {
    if (k == 0) {
        std::cout << Prefix << std::endl;
    } else {
        numbers(Prefix + "0", k - 1);
        numbers(Prefix + "1", k - 1);
    }
}

int main() {
    string Prefix;
    int k;
    std::cout << "enter a binary number: ";
    std::cin >> Prefix;
    std::cout << "enter an integer: ";
    std::cin >> k;
    numbers(Prefix,k);
}
