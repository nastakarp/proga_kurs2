#ifndef UNTITLED_STRINGLIST_H
#define UNTITLED_STRINGLIST_H

#include "../node/StringNode.h"

// Класс для списка char*
class StringList {
private:
    StringNode* head; // Указатель на начало списка
    StringNode* tail; // Указатель на конец списка

public:
    // Конструктор по умолчанию
    StringList();

    // Деструктор
    ~StringList();

    // Добавление элемента в конец списка, если его там нет
    StringNode* append(const char* value);

    // Перегрузка оператора вывода для вывода списка в поток
    friend std::ostream& operator<<(std::ostream& os, const StringList& list);
};

#endif //UNTITLED_STRINGLIST_H
