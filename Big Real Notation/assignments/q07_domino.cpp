// File: q07_domino.cpp
// Purpose: Check if a domino chain can be formed from a given set.
// Author: Belal Youness (20220087)

#include <iostream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
using namespace std;

struct dominoT {
    int leftdots;
    int rightdots;
};

bool formsdominochain(vector<dominoT> &dominos, vector<dominoT> &chain) {
    if (dominos.empty()) {
        return true;
    }

    for (int i = 0; i < dominos.size(); ++i) {
        if (chain.empty() || chain.back().rightdots == dominos[i].leftdots) {
            chain.push_back(dominos[i]);

            dominoT temp = dominos[i];
            dominos.erase(dominos.begin() + i);

            if (formsdominochain(dominos, chain)) {
                return true;
            }

            dominos.insert(dominos.begin() + i, temp);
            chain.pop_back();
        }
    }

    return false;
}

void outputdominochain(const vector<dominoT> &chain) {
    for (const dominoT &domino : chain) {
        cout << domino.leftdots << "|" << domino.rightdots << " - ";
    }
    cout << endl;
}

int main() {
    vector<dominoT> dominoSet = {
            {2, 6},
            {6, 1},
            {1, 4},
            {4, 4},
            {4, 3}
    };

    vector<dominoT> chain;
    bool canformchain = formsdominochain(dominoSet, chain);

    if (canformchain) {
        cout << "A domino chain can be formed:\n";
        outputdominochain(chain);
    } else {
        cout << "A domino chain cannot be formed.\n";
    }

    return 0;
}
