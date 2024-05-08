#include <iostream>
#include <fstream>

// Функция для определения длины строки
int length(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Функция для копирования строки
void copy(const char *source, char *destination, int len) {
    for (int i = 0; i < len; ++i) {
        destination[i] = source[i];
    }
    destination[len] = '\0'; // Добавляем завершающий нулевой символ
}

int extractYear(const char *dateStr) {
    int year = 0;
    // Ищем позицию первого символа '-'
    int pos = 0;
    while (dateStr[pos] != '-' && dateStr[pos] != '\0') {
        pos++;
    }
    // Переводим символы до первого '-' в число
    for (int i = 0; i < pos; ++i) {
        if (dateStr[i] >= '0' && dateStr[i] <= '9') {
            year = year * 10 + (dateStr[i] - '0');
        }
    }
    return year;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}

char *readUntilComma(std::ifstream &input) {
    const int bufferSize = 100; // Максимальная длина строки
    char *buffer = new char[bufferSize];
    int index = 0;
    char symbol;

    while (input.get(symbol) && symbol != EOF && symbol != ',' && symbol != '\n') {
        buffer[index++] = symbol;
        if (index >= bufferSize - 1) // Проверка на переполнение буфера
            break;
    }
    if (symbol == ',') {
        input.get(symbol);
    }
    buffer[index] = '\0'; // Добавляем завершающий нулевой символ
    return buffer;
}

int charToInt(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Преобразование каждого символа в цифру и добавление к результату
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}
