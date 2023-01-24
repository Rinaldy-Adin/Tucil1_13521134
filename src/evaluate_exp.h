#include <string>
#include <vector>

using std::string;
using std::vector;

// Evaluate expressions based off generated card permutations and possible prefix expressions
vector<string> evaluateExpressions(int permutations[][4], int nPerms, char possibleExpressions[][7],
                                   int nExps);