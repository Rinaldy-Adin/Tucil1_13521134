#include "cliui.h"

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::string;

// Read cards based off user input
void readInput(int cardNums[]) {
    // Initialize variables
    int i = 0;
    int idx = 0;
    bool spaceSeparated = true;

    // Read line from input as string
    string str;
    getline(cin >> std::ws, str);

    char c;
    // Iterate over string to ensure valid input
    while (idx < str.length()) {
        c = str[idx];

        if (c > '1' && c <= '9' && spaceSeparated) {  // Card values under 10
            cardNums[i % 4] = c - '0';
            spaceSeparated = false;
        } else if (c == '1' && spaceSeparated) {  // Handle 10
            idx++;
            c = str[idx];
            if (c == '0') {
                cardNums[i % 4] = 10;
                spaceSeparated = false;
            } else {
                cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
                return;
            }
        } else {  // Handle A J Q K and space character
            if ((c == 'A' || c == 'a') && spaceSeparated) {
                cardNums[i % 4] = 1;
                spaceSeparated = false;
            } else if ((c == 'J' || c == 'j') && spaceSeparated) {
                cardNums[i % 4] = 11;
                spaceSeparated = false;
            } else if ((c == 'Q' || c == 'q') && spaceSeparated) {
                cardNums[i % 4] = 12;
                spaceSeparated = false;
            } else if ((c == 'K' || c == 'k') && spaceSeparated) {
                cardNums[i % 4] = 13;
                spaceSeparated = false;
            } else if (c == ' ') {
                spaceSeparated = true;
                i--;
            } else {
                cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
            }
        }
        i++;
        idx++;
    }

    // Return invalid input if the number of cards given is not 4
    if (i != 4 || idx < str.length()) {
        cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
        return;
    }
}

// Display splash screen
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

// Display header with centered title
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

// Display menu and recieve valid input
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
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

// Display cards
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

// Ask for user to press enter to continue program
void waitForEnter() {
    cout << "Continue? (press enter)";
    cin.ignore(INT_MAX, '\n');
}

// Ask for user to save solution results into file
void askToSave(int cardNums[], vector<string> solutions, int nanoseconds) {
    string str;
    do {  // Validate input
        cout << "\nWould you like to save your results to a file?(y/n): ";
        getline(cin >> std::ws, str);
    } while (str[0] != 'y' && str[0] != 'Y' && str[0] != 'n' && str[0] != 'N');

    // Write to file if user inputs Y
    if (str[0] == 'y' && str[0] != 'Y') {
        do {
            cout << "Enter the path to your file: ";
            getline(cin >> std::ws, str);
            ofstream outfile;

            try {
                outfile.open(str);
                outfile << "Cards: ";

                for (int i = 0; i < 4; i++) {
                    switch (cardNums[i]) {
                        case 1:
                            outfile << "A ";
                            break;
                        case 11:
                            outfile << "J ";
                            break;
                        case 12:
                            outfile << "Q ";
                            break;
                        case 13:
                            outfile << "K ";
                            break;
                        default:
                            outfile << cardNums[i] << " ";
                            break;
                    }
                }
                outfile << endl << endl;

                outfile << solutions.size() << " solutions found" << endl << endl;
                for (string solution : solutions) {
                    outfile << solution << endl;
                }

                outfile << "\nSolution algorithm elapsed for " << std::fixed << std::setprecision(3)
                        << nanoseconds * 1e-6 << " miliseconds" << endl;

                outfile.close();
                break;
            } catch (const ofstream::failure& e) {
                outfile.close();
                cout << "Filepath not valid" << endl;
            }
        } while (true);

        cout << "\nFile successfully written!" << endl;
    }
}