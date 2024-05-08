#include "StringNode.h"
// Конструктор
StringNode::StringNode(const char* value) : next(nullptr) {
    // Выделение памяти для копии строки и копирование данных
    int len = length(value);
    data = new char[len + 1];
    copy(value, data, len);
}

// Деструктор для освобождения памяти
StringNode::~StringNode() {
    delete[] data; // Освобождаем память, выделенную для данных
}

// Оператор сравнения равенства NameNode
bool operator==(const StringNode &lhs, const StringNode &rhs) {
    // Сравниваем данные игроков
    return strcmp(lhs.data, rhs.data) == 0;
}
