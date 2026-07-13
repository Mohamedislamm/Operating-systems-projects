#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>

// File: q05_high_score.cpp
// Purpose: High score manager with sorting and search.
// Author: Mohamed Islam Khaled (20220282)

using namespace std;

class player {
public:
    string name;
    int score;

    player(string name, int score) {
        this->name = name;
        this->score = score;
    }
};
vector<player>players;

int main() {
    int input;
    string name;
    int score;
    cout << "Welcome to the high score manager, please choose one of the following:\n";
    do {
        cout<<"1- Add a new player and score.\n"
              "2- Print the top 10 names and scores.\n"
              "3- Enter a player name to show that player's highest score if it is on the top 10 list.\n"
              "4- Exit menu.\n";
        cin >> input;
        switch (input) {
            case 1: {
                cout << "Enter player's name: ";
                cin >> name;
                cout << "Enter player's score: ";
                cin >> score;
                player player(name, score);
                players.push_back(player);
                break;
            }
            case 2: {
                sort(players.begin(), players.end(), [](const player &p1, const player &p2) {
                    return p1.score > p2.score;
                });
                cout << "Top 10 Scores list:\n";
                int z;
                if(players.size()>10){
                    z=players.size();
                }
                else{
                    z=10;
                }
                for (int i = 0; i < z; i++) {
                    cout << players[i].name << ": " << players[i].score << "\n";
                }
                break;
            }
            case 3: {
                cout << "Enter player's name: ";
                cin >> name;
                int x;
                sort(players.begin(), players.end(), [](const player &p1, const player &p2) {
                    return p1.score > p2.score;
                });
                for (int i = 0; i < 10; i++) {
                    if (players[i].name == name) {
                        x = players[i].score;
                        break;
                    } else {
                        x = -1;
                    }
                }
                score = x;
                if (score != -1) {
                    cout << name << "'s highest score in the top 10 list: " << score << "\n";
                } else {
                    cout << "Player not found in top 10 list.\n";
                }
                break;
            }
            case 4: {
                cout << "Thank you for using our list manager.";
                break;
            }
            default: {
                cout << "Wrong input, please try again.";
            }
        }
    }while (input != 4);
    return 0;
}
