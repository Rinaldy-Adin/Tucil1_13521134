#include <chrono>
#include <iostream>
#include <vector>

#include "evaluate_exp.h"
#include "generate_exp.h"
#include "generate_perms.h"
#include "precomp.h"

using std::cout;
using std::endl;
using std::vector;

/*
    CHECK FOR: 10 3 9 6
*/

int main() {
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

    readInput(cardNums);

    if (cardNums[0] != -1) {
        auto begin = std::chrono::high_resolution_clock::now();

        generatePermutations(cardNums, permutations, &nPermutations);
        generateExpressions(possibleExpressions, &nExpressions);
        vector<string> expressions =
            evaluateExpressions(permutations, nPermutations, possibleExpressions, nExpressions);

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        cout << expressions.size() << " solutions found:" << endl << endl;
        for (string expression : expressions) {
            cout << expression << endl;
        }

        printf("\nAlgorithms elapsed for %.3f miliseconds\n", elapsed.count() * 1e-6);
    } else {
        printf(
            "\nInput invalid, enter 4 card values separated by spaces\n(A, 2, 3, 4, 5, 6, 7, 8, 9, "
            "10, J, Q, K)\n");
    }

    return 0;
}