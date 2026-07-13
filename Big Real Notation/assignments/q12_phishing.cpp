// File: q12_phishing.cpp
// Purpose: Detect phishing terms in a text file and score them.
// Author: mohammed gamal abd el nasser Atteya (20221119)

#include <iostream>
#include <map>
#include <string>
#include <fstream>
using std::string;

std::map<string,int> phishingTerms=
        {
                {"free netflix pass",3},
                {"click here to download",1},
                {"credit card",3},
                {"account",2},
                {"bank",2},
                {"verify",2},
                {"password",3},
                {"urgent",2},
                {"social security",3},
                {"winner",2},
                {"click",1},
                {"account suspended",3},
                {"discount",1},
                {"free",1},
                {"limited time",2},
                {"update",2},
                {"confirm your identity",3},
                {"prize",2},
                {"unsubscribe",1},
                {"earn money fast",3},
                {"online pharmacy",3},
                {"exclusive deal",2},
                {"lottery",2},
                {"secret",2},
                {"send us your verification code",2},
                {"million dollars",3},
                {"claim ur gift",2},
                {"u won a free ",1},
                {"click here for free windows defender ",2},
        };

int main()
{
    string filename;
    std::cout<<"Enter files name to check for phishing: ";
    std::cin>>filename;

    std::ifstream file(filename);
    if (!file)
    {
        std::cerr<<"error couldnt open file"<<std::endl;
        return 1;
    }
    string text,line;
    while (std::getline(file, line))
    {
        text += line + '\n';
    }
    std::map<string, int> termCounts;
    int totalPoints = 0;

    for (const auto& termValue : phishingTerms)
    {
        const string& term = termValue.first;
        int points = termValue.second;
        size_t pos = 0;
        while ((pos = text.find(term, pos)) != string::npos)
        {
            totalPoints += points;
            termCounts[term]++;
            pos += term.length();
        }
    }
    file.close();

    std::cout<<"Phishing terms found in the input text:"<<std::endl;
    for(const auto& termCount:termCounts)
    {
        std::cout<<termCount.first <<": "<<termCount.second<<"points"<<std::endl;
    }
    std::cout << "total points in file:"<<totalPoints<<"points"<<std::endl;
}
