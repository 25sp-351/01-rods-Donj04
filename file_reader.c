#include "file_reader.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "keypair.h"

bool isBlankLine(char *line) {
    if (line[0] == '#')
        return true;
    for (int i = 0; i < strlen(line); i++)
        if (!isspace(line[i]))
            return false;
    return true;
}

char *trimNewline(char *text) {
    size_t size = strlen(text);
    if (size > 0 && text[size - 1] == '\n')
        text[size - 1] = '\0';
    return text;
}

bool extractFile(char filename[]) {
    printf("Reading %s\n", filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening %s\n", filename);
        return false;
    }

    char line[FILE_MAX_LINE_LENGTH];

    while (fgets(line, FILE_MAX_LINE_LENGTH, file))
        if (!isBlankLine(line)) {
            int length;
            int value;
            // If either variable was not successfully converted, return error
            if (sscanf(line, "%d,%d", &length, &value) != 2) {
                printf(
                    "ERROR: line \"%s\" is invalid. Format should be "
                    "<int>,<int>\n",
                    trimNewline(line));
                return false;
            }
            printf("%s\n", trimNewline(line));
        } else
            printf("Ignoring %s\n", trimNewline(line));

    fclose(file);
    return true;
}
