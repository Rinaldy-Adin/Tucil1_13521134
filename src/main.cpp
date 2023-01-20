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

    return 0;
}