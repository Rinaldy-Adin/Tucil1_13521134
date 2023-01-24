#include <string>
#include <vector>

using std::string;
using std::vector;

// Read cards based off user input
void readInput(int cardNums[]);

// Display splash screen
void splashScreen();

// Display header with centered title
void header(string str);

// Display menu and recieve valid input
int menuPrompt(string prompt, vector<string> choices);

// Display cards
void printCards(int cardNums[]);

// Ask for user to press enter to continue program
void waitForEnter();

// Ask for user to save solution results into file
void askToSave(int cardNums[], vector<string> solutions, int nanoseconds);