#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdbool.h>

#define FILE_MAX_LINES 128
#define FILE_MAX_LINE_LENGTH 128

bool isBlankLine(char *line);

char* trimNewline(char *text);

bool extractFile(char filename[]);

#endif