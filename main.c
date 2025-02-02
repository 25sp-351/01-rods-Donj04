#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filereader.h"
#include "rodcutsolver.h"

void processInput(Vec prices, char* input) {
    input[strcspn(input, "\n")] = 0;
    long int length;  // is long int to detect if input is larger than 32-bit
                      // int limit
    if (validateLength(input, &length)) {
        RodCutSolver solver = createRodCutSolver(prices);
        solveRodCutting(solver, (int)length);
        freeRodCutSolver(solver);
    } else
        printf("Rod length must be a 32-bit integer greater than 0.\n");
}

int main(int argc, char* argv[]) {
    if (validateInput(argc, argv)) {
        Vec length_prices = extractFile(argv[2]);

        if (vec_length(length_prices) == 0) {
            printf("ERROR: File does not contain any valid length values\n");
            return 1;
        }

        char input[100];
        strcpy(input, argv[1]);
        do {
            processInput(length_prices, input);
            printf("Enter another length (EOF to exit): ");
            fgets(input, 100, stdin);
        } while (!feof(stdin));

        printf("\n");
        return 0;
    }
    return 1;
}
