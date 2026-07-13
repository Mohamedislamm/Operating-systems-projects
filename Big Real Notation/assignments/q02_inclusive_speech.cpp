#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>

// File: q02_inclusive_speech.cpp
// Purpose: Turn male speech into inclusive speech that includes both male and female.
// Author: Mohamed Islam Khaled (20220282)

int main() {
    using namespace std;
    string s;
    getline(cin,s);

    for(int i=0;i<1000;i++) {
        int index = s.find(" he ");
        if (index != -1) {
            s.replace(index, 4, " xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " he or she ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find("He ");
        if (index != -1) {
            s.replace(index, 3, "xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find("xyz ");
        if (index != -1) {
            s.replace(index, 4, "He or she ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find("Him ");
        if (index != -1) {
            s.replace(index, 4, "xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find("xyz ");
        if (index != -1) {
            s.replace(index, 4, "Him or her ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" him ");
        if (index != -1) {
            s.replace(index, 5, " xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " him or her ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" him.");
        if (index != -1) {
            s.replace(index, 5, " xyz ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " him or her.");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" him?");
        if (index != -1) {
            s.replace(index, 5, " xyz ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " him or her?");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" him,");
        if (index != -1) {
            s.replace(index, 5, " xyz ");
        }
    }
    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " him or her,");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" he.");
        if (index != -1) {
            s.replace(index, 4, " xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " he or she.");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" he,");
        if (index != -1) {
            s.replace(index, 4, " xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " he or she,");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" he?");
        if (index != -1) {
            s.replace(index, 4, " xyz ");
        }
    }

    for(int i=0;i<1000;i++) {
        int index = s.find(" xyz ");
        if (index != -1) {
            s.replace(index, 5, " he or she?");
        }
    }

    cout<<s;

    return 0;
}
