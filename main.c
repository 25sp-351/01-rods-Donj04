#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filereader.h"
#include "rodcutsolver.h"

// Return true if there are at least 2 command-line arguments and they are valid
bool validateInput(int argument_count, char *arguments[]) {
    int input;
    bool length_valid = false;
    bool file_valid   = false;

    if (argument_count > 2) {
        // length is valid if the 1st argument was converted correctly to int
        // and is not negative
        length_valid = (sscanf(arguments[1], "%d", &input) != 0 && input > 0);
        // File is valid if it exists
        // extractFile() will return an error if contents are invalid
        file_valid = (access(arguments[2], F_OK) == 0);

        if (!length_valid)
            printf(
                "ERROR: \"%s\" is an invalid length input. "
                "Please enter an integer greater than 0.\n",
                arguments[1]);
        if (!file_valid)
            printf("ERROR: \"%s\" is not a valid file path.\n", arguments[2]);
    } else {
        printf(
            "ERROR: Not enough arguments given. Please provide an "
            "integer and "
            "a valid file path.\n");
    }

    return (length_valid && file_valid);
}

int main(int argc, char *argv[]) {
    // Continue if inputs were valid and file was extracted correctly
    if (validateInput(argc, argv)) {
        size_t rod_length;
        sscanf(argv[1], "%zu", &rod_length);

        RodCutSolver solver = createRodCutSolver(rod_length);
        setLengthPrices(&solver, extractFile(argv[2]));
        solveRodCutting(&solver);
        return 0;
    } else {
        return 1;
    }
}
