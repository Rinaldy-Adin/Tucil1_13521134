#include <chrono>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int nums[4] = {24, 5, 5, 1};

int permutations[25][4];
int permIdx = 0;

void init() {
    for (int i = 0; i < 4; i++) {
        nums[i] = 0;
    }

    for (int i = 0; i < 25; i++) {
        permutations[i][0] = permutations[i][1] = permutations[i][2] = permutations[i][3] = 0;
    }
}

void readInput() {
    for (int i = 0; i < 4; i++) {
        char c;
        cin >> c;

        int x;
        switch (c) {
            case 'A':
                x = 1;
                break;
            case 'J':
                x = 11;
                break;
            case 'Q':
                x = 12;
                break;
            case 'K':
                x = 13;
                break;
            default:
                x = c - '0';
                break;
        }

        nums[i] = x;
    }
}

bool isInPermutations(int arr[]) {
    int i = 0;
    while (i < permIdx) {
        if (arr[0] == permutations[i][0] && arr[1] == permutations[i][1] &&
            arr[2] == permutations[i][2] && arr[3] == permutations[i][3]) {
            return true;
        }
        i++;
    }

    return false;
}

void generatePermutations() {
    for (int a = 0; a < 4; a++) {
        int generated[4];
        bool used[4] = {0, 0, 0, 0};

        generated[0] = nums[a];
        used[a] = 1;

        for (int b = 0; b < 4; b++) {
            if (used[b])
                continue;

            generated[1] = nums[b];
            used[b] = 1;

            for (int c = 0; c < 4; c++) {
                if (used[c])
                    continue;

                generated[2] = nums[c];
                used[c] = 1;

                for (int d = 0; d < 4; d++) {
                    if (used[d])
                        continue;

                    generated[3] = nums[d];
                    used[d] = 1;

                    if (!isInPermutations(generated)) {
                        for (int i = 0; i < 4; i++) {
                            permutations[permIdx][i] = generated[i];
                        }

                        permIdx++;
                    }

                    used[d] = 0;
                }

                used[c] = 0;
            }

            used[b] = 0;
        }
    }
}

char possibleExpressions[400][7];
int possibleExpressionsIdx = 0;

void generatePrefix(char toInsert, char unusedVar, char generated[], int generatedIdx,
                    int nOperators, int nNums) {
    generated[generatedIdx] = toInsert;

    if (generatedIdx == 6) {
        for (int i = 0; i < 7; i++) {
            possibleExpressions[possibleExpressionsIdx][i] = generated[i];
        }
        possibleExpressionsIdx++;
    }

    if (nOperators < 3) {
        generatePrefix('*', unusedVar, generated, generatedIdx + 1, nOperators + 1, nNums);
        generatePrefix('/', unusedVar, generated, generatedIdx + 1, nOperators + 1, nNums);
        generatePrefix('+', unusedVar, generated, generatedIdx + 1, nOperators + 1, nNums);
        generatePrefix('-', unusedVar, generated, generatedIdx + 1, nOperators + 1, nNums);
    }
    if (nNums < nOperators || generatedIdx == 5)
        generatePrefix(unusedVar, unusedVar + 1, generated, generatedIdx + 1, nOperators,
                       nNums + 1);
}

void generateExpressions() {
    char generated[7];

    generatePrefix('*', 'w', generated, 0, 1, 0);
    generatePrefix('/', 'w', generated, 0, 1, 0);
    generatePrefix('+', 'w', generated, 0, 1, 0);
    generatePrefix('-', 'w', generated, 0, 1, 0);
}

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

vector<string> infixes;

void mapAndEvaluate() {
    for (int currPerm = 0; currPerm < permIdx; currPerm++) {
        for (int currExp = 0; currExp < possibleExpressionsIdx; currExp++) {
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

            // for (int i = 0; i < 7; i++) {
            //     cout << mappedExp[i] << " ";
            // }
            // cout << endl;

            if (evaluatePrefix(mappedExp) == 24) {
                infixes.push_back(convertToInfix(mappedExp));
            }
        }
    }
}

int main() {
    init();
    readInput();

    auto begin = chrono::high_resolution_clock::now();
    generatePermutations();
    generateExpressions();
    mapAndEvaluate();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    cout << infixes.size() << " solutions found:" << endl;
    for (string infix : infixes) {
        cout << infix << endl;
    }

    printf("\nTime elapsed: %.3f miliseconds\n", elapsed.count() * 1e-6);
    return 0;
}