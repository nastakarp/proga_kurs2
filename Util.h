#ifndef PROGA_KURS_UTIL_H
#define PROGA_KURS_UTIL_H

#include <iostream>
#include <fstream>

int length(const char *str);

void copy(const char *source, char *destination, int len);

int extractYear(const char *dateStr);

int strcmp(const char *str1, const char *str2);

char *readUntilComma(std::ifstream &input);

int charToInt(const char *str);

#endif //PROGA_KURS_UTIL_H