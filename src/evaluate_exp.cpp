#include "evaluate_exp.h"

#include <stack>
#include <string>
#include <vector>

using std::stack;
using std::string;
using std::to_string;
using std::vector;

double evaluatePrefix(char mappedExp[]) {
    stack<double> Stack;

    for (int i = 6; i >= 0; i--) {
        if (mappedExp[i] > '0' && mappedExp[i] <= '9') {
            Stack.push((double)mappedExp[i] - '0');
        } else if (mappedExp[i] >= 'a' && mappedExp[i] < 'w') {
            Stack.push((double)mappedExp[i] - 'a' + 10);
        } else {
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

string convertToInfix(char infix[]) {
    stack<string> Stack;

    for (int i = 6; i >= 0; i--) {
        if (infix[i] > '0' && infix[i] <= '9') {
            string s(1, infix[i]);
            Stack.push(s);
        } else if (infix[i] >= 'a' && infix[i] < 'w') {
            Stack.push(to_string(infix[i] - 'a' + 10));
        } else {
            string y = Stack.top();
            Stack.pop();
            string x = Stack.top();
            Stack.pop();

            string z;
            if (i != 0) {
                z = "(" + x + " " + infix[i] + " " + y + ")";
            } else {
                z = x + " " + infix[i] + " " + y;
            }

            Stack.push(z);
        }
    }

    return Stack.top();
}

vector<string> evaluateExpressions(int permutations[][4], int nPerms, char possibleExpressions[][7],
                                   int nExps) {
    vector<string> infixes;

    for (int currPerm = 0; currPerm < nPerms; currPerm++) {
        for (int currExp = 0; currExp < nExps; currExp++) {
            char mappedExp[7];

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

            if (evaluatePrefix(mappedExp) == 24) {
                infixes.push_back(convertToInfix(mappedExp));
            }
        }
    }

    return infixes;
}
