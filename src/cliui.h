#include <string>
#include <vector>

using std::string;
using std::vector;

void readInput(int cardNums[]);

void splashScreen();

void header(string str);

int menuPrompt(string prompt, vector<string> choices);

void printCards(int cardNums[]);

void waitForEnter();