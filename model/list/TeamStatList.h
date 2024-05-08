#ifndef PROGA_KURS_TEAMSTATLIST_H
#define PROGA_KURS_TEAMSTATLIST_H

#include <iostream>
#include "../node/TeamStatNode.h"

struct TeamStatList {
    TeamStatNode *head; // Указатель на начало списка
    TeamStatNode *tail; // Указатель на конец списка

    // Конструктор по умолчанию
    TeamStatList();

    // Деструктор для освобождения памяти
    ~TeamStatList();

    // Добавление узла в конец списка
    void appendNode(const TeamStat& value);

    // Оператор вывода узла в поток
    friend std::ostream &operator<<(std::ostream &os, const TeamStatList &list);
};

#endif //PROGA_KURS_TEAMSTATLIST_H
