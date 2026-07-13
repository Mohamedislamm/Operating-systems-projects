#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

// File: q11_file_compare.cpp
// Purpose: Compare two text files character-by-character or word-by-word.
// Author: Mohamed Islam Khaled (20220282)

using namespace std;

bool charcompare(const string& file1, const string& file2) {
    ifstream f1(file1);
    ifstream f2(file2);
    string line1, line2;
    int lineindex = 0;

    while (getline(f1, line1) && getline(f2, line2)) {
        lineindex++;
        for (int i = 0; i < min(line1.length(), line2.length()); i++) {
            if (line1[i] != line2[i]) {
                cout << "Files are different at line " << lineindex << ", character " << i + 1 << ":" << endl;
                cout << "File 1: " << line1[i] << endl;
                cout << "File 2: " << line2[i] << endl;
                return false;
            }
        }

        if (line1.length() != line2.length()) {
            cout << "Files are different at line " << lineindex << ", character " << min(line1.length(), line2.length()) + 1 << ":" << endl;
            cout <<"Difference at end of Line" << endl;
            return false;
        }
    }

    if (!f1.eof() || !f2.eof()) {
        cout << "Files are different at line " << lineindex + 1 << ", character 1:" << endl;
        return false;
    }

    cout << "Files are identical." << endl;
    return true;
}

bool wordcompare(const string& file1, const string& file2) {
    ifstream f1(file1);
    ifstream f2(file2);
    string word1, word2;
    int lineindex = 1;
    while (f1 >> word1 && f2 >> word2) {
        if (word1 != word2) {
            cout << "Files are different at word " << word1 << " on line " << lineindex << ":" << endl;
            cout << "File 1: " << word1 << endl;
            cout << "File 2: " << word2 << endl;
            return false;
        }
        while (getline(f1, word1, '\n') && getline(f2, word2, '\n')) {
            if (word1 != word2) {
                cout << "Files are different at word '" << word1 << "' on line " << lineindex << ":" << endl;
                cout << "File 1: " << word1 << endl;
                cout << "File 2: " << word2 << endl;
                return false;
            }
            lineindex++;
        }
    }

    if (!f1.eof() || !f2.eof()) {
        cout << "Files are different at word " << "End of File" << " on line " << lineindex + 1 << ":" << endl;
        cout << "File 1: " << "End of File" << endl;
        cout << "File 2: " << "End of File" << endl;
        return false;
    }

    cout << "Files are identical." << endl;
    return true;
}

int main() {
    string file1, file2;
    int choice;
    cout << "Enter name of the first file: ";
    cin >> file1;
    cout << "Enter name of the second file: ";
    cin >> file2;
    cout << "Please choose comparison type:\n"
            "1- Compare character by character.\n"
            "2- Compare word by word.\n";
    cin >> choice;

    if (choice == 1) {
        charcompare(file1,file2);
    }
    else if (choice == 2) {
        wordcompare(file1, file2);
    }
    else{
        cout << "Incorrect input, Please try again." << endl;
    }

    return 0;
}
