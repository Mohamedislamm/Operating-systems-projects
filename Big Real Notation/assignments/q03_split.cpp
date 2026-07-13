// File: q03_split.cpp
// Purpose: Split a string by a delimiter and return a vector of parts.
// Author: mohammed gamal abd el nasser Atteya (20221119)

#include <iostream>
#include <vector>
using std::string;
using std::vector;

vector<string> split(string target, string delimiter) {
    vector<string> result;
    string tmp;
    for (int i = 0; i < target.length(); ++i) {
        if (target[i] != delimiter[0])
        {
            tmp += target[i];
            if (i == target.length() - 1)
            {
                result.push_back(tmp);
            }
        } else if (target[i] == delimiter[0])
        {
            result.push_back(tmp);
            tmp="";
        }
    }
    return result;
}

int main() {
    string target,delimiter;
    std::cout << "Enter ur string: " ;
    getline(std::cin, target);
    std::cout << "enter delimiter: " ;
    getline(std::cin, delimiter);
    vector<string> result=split(target,delimiter);
    for(int i = 0; i < result.size();++i)
    {
        std::cout << result[i] <<" ";
    }
    return 0;
}
