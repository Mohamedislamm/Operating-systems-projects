// File: q01_sentence_formatting.cpp
// Purpose: Format a sentence with proper capitalization and spacing.
// Author: Belal Youness (20220087)

#include <iostream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main() {
    const int maxsentencelength = 100;
    char sentence[maxsentencelength];
    cout << "Enter a sentence (up to 100 characters): ";
    cin.getline(sentence, maxsentencelength);
    bool startsentence = true;
    bool newword = true;
    char prevchar = '\0';

    cout << "Output sentence: ";

    for (int i = 0; sentence[i] != '\0'; i++) {
        char currentchar = sentence[i];

        if(startsentence) {
            currentchar = toupper(currentchar);
            startsentence = false;
        }
        else if (isupper(currentchar) && newword) {
            currentchar = tolower(currentchar);
        }

        if (currentchar == ' ' || currentchar == '\n') {
            if (prevchar != ' ' && prevchar != '\n') {
                cout << ' ';
                newword = true;
            }
        }
        else {
            cout << currentchar;
            newword = false;
        }
        prevchar = currentchar;
    }
    cout << endl;

    return 0;
}
