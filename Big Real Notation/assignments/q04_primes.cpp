// File: q04_primes.cpp
// Purpose: Print prime numbers up to N using the Sieve of Eratosthenes.
// Author: Belal Youness (20220087)

#include <iostream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
using namespace std;

void sieveoferatosthenes(int N) {
    vector<bool> prime(N + 1, true);

    for (int p = 2; p * p <= N; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= N; i += p) {
                prime[i] = false;
            }
        }
    }

    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    int N;
    cout << "Enter a limit for prime numbers (N): ";
    cin >> N;

    cout << "Prime numbers between 2 and " << N << " are: ";
    sieveoferatosthenes(N);

    return 0;
}
