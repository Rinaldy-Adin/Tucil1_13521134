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
    // Splash screen on start
    splashScreen();
    cout << endl << endl;

    // Initialize loop variables
    bool programRunning = true;
    vector<string> menuChoices = {"User input", "Random", "Exit program"};

    while (programRunning) {
        // Input method menu
        header("Menu");
        cout << endl;
        int choice = menuPrompt("Choose card input method:", menuChoices);

        if (choice == 1 || choice == 2) {  // User chooses to continue
            // Initialize permutation variables
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

            if (choice == 1) {  // Cards chosen by user
                cout << "\nEnter 4 card values separated by spaces (A, 2, 3, 4, 5, 6, 7, 8, 9, 10, "
                        "J, Q, K):\n";
                readInput(cardNums);
                cout << endl;
            } else {  // Cards randomized
                for (int i = 0; i < 4; i++) {
                    cardNums[i] = rand() % 13 + 1;
                }
                cout << endl << endl;
            }

            if (cardNums[0] != -1) {  // Input valid
                // Display cards chosen by user/random
                header("Cards");
                printCards(cardNums);
                waitForEnter();
                cout << endl << endl;

                // Start algorithm clock
                auto begin = std::chrono::high_resolution_clock::now();

                // Generate & evaluate expressions equal to 24
                generatePermutations(cardNums, permutations, &nPermutations);
                generateExpressions(possibleExpressions, &nExpressions);
                vector<string> expressions = evaluateExpressions(permutations, nPermutations,
                                                                 possibleExpressions, nExpressions);

                // End algorithm clock and calculate elapsed time
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                // Display solutions
                header("Solutions");
                cout << expressions.size() << " solutions found:" << endl << endl;
                for (string expression : expressions) {
                    cout << expression << endl;
                }

                // Display elapsed time
                cout << "\nSolution algorithm elapsed for " << std::fixed << std::setprecision(3)
                     << elapsed.count() * 1e-6 << " miliseconds\n";

                // Ask user to save to file
                askToSave(cardNums, expressions, elapsed.count());

            } else {  // Input Invalid
                // Return to menu
                cout << "\nInput invalid\n";
                waitForEnter();
            }
            cout << endl << endl;

        } else {  // User chooses to exit program
            programRunning = false;
        }
    }

    return 0;
}