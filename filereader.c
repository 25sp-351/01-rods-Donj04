#include "filereader.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

Vec extractFile(char filename[]) {
    printf("Reading %s\n", filename);

    FILE* file  = fopen(filename, "r");

    Vec lengths = new_vec(sizeof(KeyPair));

    if (file == NULL) {
        printf("Error opening %s\n", filename);
    } else {
        char line[FILE_MAX_LINE_LENGTH];

        while (fgets(line, FILE_MAX_LINE_LENGTH, file)) {
            if (isBlankLine(line)) {
                printf("Ignoring %s\n", trimNewline(line));
            } else {
                int length;
                int value;
                // Convert numbers and check if valid for both
                if (2 == sscanf(line, "%d,%d", &length, &value) && length >= 0) {
                    KeyPair pair = createKeyPair(length, value);
                    vec_add(lengths, &pair);
                    printf("Added length %d, $%d\n", length, value);
                } else {
                    printf(
                        "ERROR: line \"%s\" in %s is invalid. Format should be "
                        "<+int>,<int>\n",
                        trimNewline(line), filename);
                    // break;
                }
            }
        }
    }
    fclose(file);
    return lengths;
}
