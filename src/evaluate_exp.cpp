#include "evaluate_exp.h"

#include <stack>
#include <string>
#include <vector>

using std::stack;
using std::string;
using std::to_string;
using std::vector;

// Return value of prefix equation
double evaluatePrefix(char mappedExp[]) {
    stack<double> Stack;

    // Iterate from back to front
    for (int i = 6; i >= 0; i--) {
        if (mappedExp[i] > '0' &&
            mappedExp[i] <= '9') {  // Push numericals into stack & cast to double
            Stack.push((double)mappedExp[i] - '0');
        } else if (mappedExp[i] >= 'a' &&
                   mappedExp[i] < 'w') {  // Push numericals into stack & cast to double
            Stack.push((double)mappedExp[i] - 'a' + 10);
        } else {  // Pop & calculate top two numericals and push result into stack when operator
                  // found in
            double y = Stack.top();
            Stack.pop();
            double x = Stack.top();
            Stack.pop();

            if (mappedExp[i] == '*') {
                Stack.push(x * y);
            } else if (mappedExp[i] == '/') {
                Stack.push(x / y);
            } else if (mappedExp[i] == '+') {
                Stack.push(x + y);
            } else if (mappedExp[i] == '-') {
                Stack.push(x - y);
            }
        }
    }

    return Stack.top();
}

// Convert prefix array of chars into infix string
string convertToInfix(char prefix[]) {
    stack<string> Stack;

    // Iterate from back to front
    for (int i = 6; i >= 0; i--) {
        if (prefix[i] > '0' && prefix[i] <= '9') {  // Push numericals into stack & cast to string
            string s(1, prefix[i]);
            Stack.push(s);
        } else if (prefix[i] >= 'a' &&
                   prefix[i] < 'w') {  // Push numericals into stack & cast to string
            Stack.push(to_string(prefix[i] - 'a' + 10));
        } else {  // Pop top two numericals and push infix expressions into stack when operator
                  // found in prefix
            string y = Stack.top();
            Stack.pop();
            string x = Stack.top();
            Stack.pop();

            string z;
            if (i != 0) {
                z = "(" + x + " " + prefix[i] + " " + y + ")";
            } else {
                z = x + " " + prefix[i] + " " + y;
            }

            Stack.push(z);
        }
    }

    return Stack.top();
}

// Evaluate expressions based off generated card permutations and possible prefix expressions
vector<string> evaluateExpressions(int permutations[][4], int nPerms, char possibleExpressions[][7],
                                   int nExps) {
    vector<string> infixes;

    // Iterate over permutations of cards and expressions
    for (int currPerm = 0; currPerm < nPerms; currPerm++) {
        for (int currExp = 0; currExp < nExps; currExp++) {
            char mappedExp[7];

            // Cast permutations of type int to characters representing hexadecimals
            for (int k = 0; k < 7; k++) {
                char mappedOp = possibleExpressions[currExp][k];
                if (mappedOp >= 'w' && mappedOp <= 'z') {
                    mappedExp[k] = permutations[currPerm][mappedOp - 'w'] + '0';
                    if (mappedExp[k] > '9') {
                        mappedExp[k] = mappedExp[k] - '9' - 1 + 'a';
                    }
                } else {
                    mappedExp[k] = mappedOp;
                }
            }

            // Evaluate permutation and append to solutions list if equals 24
            if (evaluatePrefix(mappedExp) == 24) {
                infixes.push_back(convertToInfix(mappedExp));
            }
        }
    }

    return infixes;
}
