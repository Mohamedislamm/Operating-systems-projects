#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>

// File: q08_pattern.cpp
// Purpose: Output a recursive asterisk pattern from two inputs.
// Author: Mohamed Islam Khaled (20220282)

using namespace std;

void pattern(int n, int i) {
    string asterisks(n,'*');
    string blanks(i,' ');
    if (n == 1) {
        cout<<blanks<<"*\n";
    }
    else{
        pattern(n/2,i);
        cout<<blanks<<asterisks<<endl;
        pattern(n/2,i+n/2);
    }
}

int main(){
    int n,i;
    cout<<"Enter n:";
    cin>>n;
    cout<<"Enter i:";
    cin>>i;
    pattern(n,i);
    return 0;
}
