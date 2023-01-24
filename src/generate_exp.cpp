#include "generate_exp.h"

// Generate prefix with 4 numbers and 3 operators, following the rule that up until the last
// operand, there are more or equal operators than operands
void generatePrefix(char possibleExpressions[][7], char toInsert, char unusedVar, char generated[],
                    int generatedIdx, int nOperators, int nNums, int *nExpressions) {
    generated[generatedIdx] = toInsert;

    // Prefix expression is complete
    if (generatedIdx == 6) {
        // Insert into array
        for (int i = 0; i < 7; i++) {
            possibleExpressions[*nExpressions][i] = generated[i];
        }
        *nExpressions += 1;
    }

    if (nOperators < 3) {  // Generate operators
        generatePrefix(possibleExpressions, '*', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
        generatePrefix(possibleExpressions, '/', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
        generatePrefix(possibleExpressions, '+', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
        generatePrefix(possibleExpressions, '-', unusedVar, generated, generatedIdx + 1,
                       nOperators + 1, nNums, nExpressions);
    }

    // Generate numbers when possible or when last operand
    if (nNums < nOperators || generatedIdx == 5)
        generatePrefix(possibleExpressions, unusedVar, unusedVar + 1, generated, generatedIdx + 1,
                       nOperators, nNums + 1, nExpressions);
}

// Generate possible expressions with w, x, y, and z as placeholders for numerical values
void generateExpressions(char possibleExpressions[][7], int *nExpressions) {
    char generated[7];
    *nExpressions = 0;

    generatePrefix(possibleExpressions, '*', 'w', generated, 0, 1, 0, nExpressions);
    generatePrefix(possibleExpressions, '/', 'w', generated, 0, 1, 0, nExpressions);
    generatePrefix(possibleExpressions, '+', 'w', generated, 0, 1, 0, nExpressions);
    generatePrefix(possibleExpressions, '-', 'w', generated, 0, 1, 0, nExpressions);
}