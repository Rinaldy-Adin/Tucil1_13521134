#include "generate_exp.h"

void generatePrefix(char possibleExpressions[][7], char toInsert, char unusedVar, char generated[],
                    int generatedIdx, int nOperators, int nNums, int *nExpressions) {
    generated[generatedIdx] = toInsert;

    if (generatedIdx == 6) {
        for (int i = 0; i < 7; i++) {
            possibleExpressions[*nExpressions][i] = generated[i];
        }
        *nExpressions += 1;
    }

    if (nOperators < 3) {
        generatePrefix(possibleExpressions, '*', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
        generatePrefix(possibleExpressions, '/', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
        generatePrefix(possibleExpressions, '+', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
        generatePrefix(possibleExpressions, '-', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
    }
    if (nNums < nOperators || generatedIdx == 5)
        generatePrefix(possibleExpressions, unusedVar, unusedVar + 1, generated, generatedIdx + 1,
                       nOperators, nNums + 1, nExpressions);
}

void generateExpressions(char possibleExpressions[][7], int *nExpressions) {
    char generated[7];
    *nExpressions = 0;

    generatePrefix(possibleExpressions, '*', 'w', generated, 0, 1, 0, nExpressions);
    generatePrefix(possibleExpressions, '/', 'w', generated, 0, 1, 0, nExpressions);
    generatePrefix(possibleExpressions, '+', 'w', generated, 0, 1, 0, nExpressions);
    generatePrefix(possibleExpressions, '-', 'w', generated, 0, 1, 0, nExpressions);
}