#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include "cliui.h"
#include "evaluate_exp.h"
#include "generate_exp.h"
#include "generate_perms.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
    splashScreen();
    cout << endl << endl;
    bool programRunning = true;
    vector<string> menuChoices = {"User input", "Random", "Exit program"};

    while (programRunning) {
        header("Menu");
        cout << endl;
        int choice = menuPrompt("Choose card input method:", menuChoices);

        if (choice == 1 || choice == 2) {
            int cardNums[4];
            int permutations[25][4];
            char possibleExpressions[400][7];

            int nPermutations;
            int nExpressions;

            for (int i = 0; i < 25; i++) {
                for (int j = 0; j < 4; j++) {
                    permutations[i][j] = 0;
                }
            }

            for (int i = 0; i < 400; i++) {
                for (int j = 0; j < 7; j++) {
                    possibleExpressions[i][j] = 0;
                }
            }

            if (choice == 1) {
                cout << "\nEnter 4 card values separated by spaces (A, 2, 3, 4, 5, 6, 7, 8, 9, 10, "
                        "J, Q, K):\n";
                readInput(cardNums);
                cout << endl;
            } else {
                for (int i = 0; i < 4; i++) {
                    cardNums[i] = rand() % 13 + 1;
                }
                cout << endl << endl;
            }

            if (cardNums[0] != -1) {
                header("Cards");
                printCards(cardNums);
                waitForEnter();
                cout << endl << endl;

                auto begin = std::chrono::high_resolution_clock::now();

                generatePermutations(cardNums, permutations, &nPermutations);
                generateExpressions(possibleExpressions, &nExpressions);
                vector<string> expressions = evaluateExpressions(permutations, nPermutations,
                                                                 possibleExpressions, nExpressions);

                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                header("Solutions");
                cout << expressions.size() << " solutions found:" << endl << endl;
                for (string expression : expressions) {
                    cout << expression << endl;
                }

                cout << "\nSolution algorithm elapsed for " << std::fixed << std::setprecision(3)
                     << elapsed.count() * 1e-6 << " miliseconds\n";
                waitForEnter();
            } else {
                cout << "\nInput invalid\n";
                waitForEnter();
            }
            cout << endl << endl;
        } else {
            programRunning = false;
        }
    }

    return 0;
}