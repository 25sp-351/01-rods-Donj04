#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filereader.h"
#include "rodcutsolver.h"

int main(int argc, char *argv[]) {
    // Continue if inputs were valid and file was extracted correctly
    if (validateInput(argc, argv)) {
        size_t rod_length;
        sscanf(argv[1], "%zu", &rod_length);

        RodCutSolver solver = createRodCutSolver(rod_length);
        setLengthPrices(solver, extractFile(argv[2]));

        solveRodCutting(solver);

        freeRodCutSolver(solver);
        return 0;
    } else {
        return 1;
    }
}
