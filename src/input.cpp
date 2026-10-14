// input.cpp
// Safe keyboard input: never crashes on bad input. (Step 3)
#include "input.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

void clearLine() {
    cin.clear();                                       // reset error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // drop the line
}

int readInt(const string& prompt, int minV, int maxV) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minV && v <= maxV) return v;
        if (cin.eof()) exit(0);
        cout << "  Invalid input, enter a number from " << minV
             << " to " << maxV << ".\n";
        clearLine();
    }
}

double readDouble(const string& prompt, double minV) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minV) return v;
        if (cin.eof()) exit(0);
        cout << "  Invalid input, enter a number >= " << minV << ".\n";
        clearLine();
    }
}

bool readYesNo(const string& prompt) {
    char c;
    while (true) {
        cout << prompt;
        if (!(cin >> c)) exit(0);
        if (c == 'y' || c == 'Y') return true;
        if (c == 'n' || c == 'N') return false;
        cout << "  Please enter y or n.\n";
    }
}

string readName(const string& prompt) {
    string s;
    clearLine();                  // drop the '\n' left by the last cin >>
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) exit(0);
        if (!s.empty()) return s;
        cout << "  Name cannot be empty.\n";
    }
}
