#ifndef UNTITLED_INTLIST_H
#define UNTITLED_INTLIST_H

#include "../node/IntNode.h"

// Класс для списка int
struct IntList {

    IntNode *head; // Указатель на начало списка
    IntNode *tail; // Указатель на конец списка

    // Конструктор по умолчанию
    IntList();

    // Деструктор
    ~IntList();

    // Добавление элемента в конец списка, если его там нет
    void append(int value);

    // Перегрузка оператора вывода для вывода списка в поток
    friend std::ostream &operator<<(std::ostream &os, const IntList &list);
};

#endif //UNTITLED_INTLIST_H
