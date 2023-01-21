#include "precomp.h"

#include <cstdio>

void readInput(int cardNums[]) {
    int i = 0;
    char c;
    scanf("%c", &c);
    while (i < 4) {
        if (c > '1' && c <= '9') {
            cardNums[i] = c - '0';
        } else if (c == '1') {
            scanf("%c", &c);
            if (c == '0') {
                cardNums[i] = 10;
            } else {
                cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
                return;
            }
        } else {
            switch (c) {
                case 'A':
                case 'a':
                    cardNums[i] = 1;
                    break;
                case 'J':
                case 'j':
                    cardNums[i] = 11;
                    break;
                case 'Q':
                case 'q':
                    cardNums[i] = 12;
                    break;
                case 'K':
                case 'k':
                    cardNums[i] = 13;
                    break;
                case ' ':
                    i--;
                    break;
                default:
                    cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
                    return;
            }
        }

        i++;
        scanf("%c", &c);
    }

    while (c == ' ') {
        scanf("%c", &c);
    }

    if (i == 4 && c != 10) {
        cardNums[0] = cardNums[1] = cardNums[2] = cardNums[3] = -1;
        return;
    }
}