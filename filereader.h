#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdbool.h>

#include "rodcutsolver.h"
#include "vec.h"

#define FILE_MAX_LINES 128
#define FILE_MAX_LINE_LENGTH 128

bool isBlankLine(char *line);

char *trimNewline(char *text);

// attempts to convert input string into an integer
// returns true if successful and 0 < length <= MAX_INT
bool validateLength(char* input, long int* num);

// File is valid if it exists
// extractFile() will return an error if contents are invalid
bool validateFile(char* filename);

// Return true if there are at least 2 command-line arguments and they are valid
bool validateInput(int argument_count, char *arguments[]);

Vec extractFile(char filename[]);

#endif