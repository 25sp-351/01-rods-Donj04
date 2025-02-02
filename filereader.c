#include "filereader.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "keypair.h"

bool isBlankLine(char* line) {
    if (line[0] == '#')
        return true;
    for (size_t i = 0; i < strlen(line); i++)
        if (!isspace(line[i]))
            return false;
    return true;
}

char* trimNewline(char* text) {
    size_t size = strlen(text);
    if (size > 0 && text[size - 1] == '\n')
        text[size - 1] = '\0';
    return text;
}

// Return true if there are at least 2 command-line arguments and they are valid
bool validateInput(int argument_count, char* arguments[]) {
    int input;
    bool length_valid = false;
    bool file_valid   = false;

    if (argument_count != 3) {
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
            "Usage: %s length /path/to/lengths.txt\n"
            "length = integer > 0\n",
            arguments[0]);
    }
    return (length_valid && file_valid);
}

Vec extractFile(char filename[]) {
    // printf("Reading %s\n", filename);
    FILE* file  = fopen(filename, "r");
    Vec lengths = new_vec(sizeof(KeyPair));

    if (file == NULL) {
        printf("Error opening %s\n", filename);
    } else {
        char line[FILE_MAX_LINE_LENGTH];

        while (fgets(line, FILE_MAX_LINE_LENGTH, file)) {
            if (isBlankLine(line)) {
                // printf("Ignoring %s\n", trimNewline(line));
                continue;
            }
            int length;  // is int to detect negative length
            int value;
            // Convert numbers and check if valid for both
            if (2 == sscanf(line, "%d,%d", &length, &value) && length >= 0) {
                // Check for duplicate lengths
                bool dupe = false;
                for (size_t i = 0; i < vec_length(lengths); i++) {
                    KeyPair* pair = vec_get(lengths, i);
                    if (pair->key == length) {
                        printf("ERROR: %d is a duplicate length\n", length);
                        dupe = true;
                        break;
                    }
                }
                if (!dupe) {
                    KeyPair new_pair = createKeyPair(length, value);
                    vec_add(lengths, &new_pair);
                    // printf("Added length %d, value %d\n", length, value);
                }
            } else {
                printf(
                    "ERROR: line \"%s\" in %s is invalid. Format should be "
                    "<size_t>, <int>\n",
                    trimNewline(line), filename);
                // break;
            }
        }
    }
    fclose(file);
    return lengths;
}
