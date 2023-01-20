#include "precomp.h"

#include <iostream>

using std::cin;

void readInput(int cardNums[]) {
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

        cardNums[i] = x;
    }
}