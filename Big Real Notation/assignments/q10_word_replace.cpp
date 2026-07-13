// File: q10_word_replace.cpp
// Purpose: Replace words in a text file using a mapping file.
// Author: Belal Youness (20220087)

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    wifstream fin("data/word_replace/input.txt");
    wofstream fout("data/word_replace/output.txt");
    if(fin.fail()) {cout<<"can't open input file!";return 1;}
    if(fout.fail()) {cout<<"can't open output file!";return 1;}
    wifstream inputFile("data/word_replace/mapinput.txt");
    if (!inputFile.is_open()) {
        wcerr << L"Can't open map input file!";
        return 1;
    }
    map<wstring, wstring> alpha;
    wstring good, better;
    while (inputFile >> good >> better) {
        alpha[good] = better;
    }

    wstring word;
    while (fin >> word) {
        map<wstring, wstring>::iterator cop = alpha.find(word);
        if (cop != alpha.end()) {
            fout << alpha[word] << L' ';
        } else {
            fout << word << L' ';
        }
    }
    return 0;
}
