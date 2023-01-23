#include "cliui.h"

#include <cstdio>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

void readInput(int cardNums[]) {
    int i = 0;
    int idx = 0;

    string str;
    getline(cin >> std::ws, str);

    char c;
    while (i < 4) {
        c = str[idx];

        if (c > '1' && c <= '9') {
            cardNums[i] = c - '0';
        } else if (c == '1') {
            cin >> c;
            if (c == '0') {
                cardNums[i] = 10;
            } else {
                cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
                return;
            }
        } else {
            switch (c) {
                case 'A':
                case 'a':
                    cardNums[i] = 1;
                    break;
                case 'J':
                case 'j':
                    cardNums[i] = 11;
                    break;
                case 'Q':
                case 'q':
                    cardNums[i] = 12;
                    break;
                case 'K':
                case 'k':
                    cardNums[i] = 13;
                    break;
                case ' ':
                    i--;
                    break;
                default:
                    cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
                    return;
            }
        }

        i++;
        idx++;
    }

    c = str[idx];
    while (idx < str.length() || c == ' ') {
        idx++;
        c = str[idx];
    }

    if (i != 4 || idx < str.length()) {
        cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
        return;
    }
}

void splashScreen() {
    cout << R"(
.___  ___.      ___       __  ___  _______     __  .___________.    ___    _  _    
|   \/   |     /   \     |  |/  / |   ____|   |  | |           |   |__ \  | || |   
|  \  /  |    /  ^  \    |  '  /  |  |__      |  | `---|  |----`      ) | | || |_  
|  |\/|  |   /  /_\  \   |    <   |   __|     |  |     |  |          / /  |__   _| 
|  |  |  |  /  _____  \  |  .  \  |  |____    |  |     |  |         / /_     | |   
|__|  |__| /__/     \__\ |__|\__\ |_______|   |__|     |__|        |____|    |_|   
    )" << endl;
}

void header(string str) {
    for (int i = 0; i < 20; i++) {
        cout << "=";
    }
    cout << "\n";

    cout << "==";
    for (int i = 2; i < 10 - (str.length() / 2); i++) {
        cout << " ";
    }
    cout << str;

    for (int i = 10 - (str.length() / 2) + str.length(); i < 18; i++) {
        cout << " ";
    }
    cout << "==\n";
    for (int i = 0; i < 20; i++) {
        cout << "=";
    }
    cout << "\n";
}

int menuPrompt(string prompt, vector<string> choices) {
    while (true) {
        cout << prompt << endl;

        for (int i = 1; i <= choices.size(); i++) {
            cout << i << ". ";
            cout << choices[i - 1] << endl;
        }

        cout << endl;
        cout << "Enter command (";

        for (int i = 1; i <= choices.size(); i++) {
            cout << i;
            if (i != choices.size())
                cout << "/";
        }
        cout << "):" << endl;

        int choice;
        cin >> choice;

        if (choice < 1 || choice > choices.size()) {
            cout << endl << "Invalid input" << endl << endl;
        } else {
            return choice;
        }
    }
}

void printCards(int cardNums[]) {
    cout << "----- ----- ----- -----" << endl;
    cout << "|   | |   | |   | |   |" << endl;

    for (int i = 0; i < 4; i++) {
        cout << "|";
        if (cardNums[i] == 11) {
            cout << " J";
        } else if (cardNums[i] == 1) {
            cout << " A";
        } else if (cardNums[i] == 12) {
            cout << " Q";
        } else if (cardNums[i] == 13) {
            cout << " K";
        } else if (cardNums[i] == 10) {
            cout << "10";
        } else {
            cout << " " << cardNums[i];
        }
        cout << " | ";
    }
    cout << endl;

    cout << "|   | |   | |   | |   |" << endl;
    cout << "----- ----- ----- -----" << endl;
}

void waitForEnter() {
    cout << "Continue? (press enter)";
    cin.ignore(INT_MAX, '\n');
}