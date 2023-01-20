#include "generate_perms.h"

bool isInPermutations(int permutation[], int permutations[][4], int last_empty_idx) {
    int i = 0;
    while (i < last_empty_idx) {
        if (permutation[0] == permutations[i][0] && permutation[1] == permutations[i][1] &&
            permutation[2] == permutations[i][2] && permutation[3] == permutations[i][3]) {
            return true;
        }
        i++;
    }

    return false;
}

void generatePermutations(int cardNums[], int permutations[][4], int *nPermutations) {
    *nPermutations = 0;

    for (int a = 0; a < 4; a++) {
        int generated[4];
        bool used[4] = {0, 0, 0, 0};

        generated[0] = cardNums[a];
        used[a] = 1;

        for (int b = 0; b < 4; b++) {
            if (used[b])
                continue;

            generated[1] = cardNums[b];
            used[b] = 1;

            for (int c = 0; c < 4; c++) {
                if (used[c])
                    continue;

                generated[2] = cardNums[c];
                used[c] = 1;

                for (int d = 0; d < 4; d++) {
                    if (used[d])
                        continue;

                    generated[3] = cardNums[d];
                    used[d] = 1;

                    if (!isInPermutations(generated, permutations, *nPermutations)) {
                        for (int i = 0; i < 4; i++) {
                            permutations[*nPermutations][i] = generated[i];
                        }

                        *nPermutations += 1;
                    }

                    used[d] = 0;
                }

                used[c] = 0;
            }

            used[b] = 0;
        }
    }
}
