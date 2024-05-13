#ifndef PROGA_KURS_PLAYERLIST_H
#define PROGA_KURS_PLAYERLIST_H

#include <iostream>
#include "../node/PlayerNode.h"

struct PlayerList {
    PlayerNode *head; // Указатель на начало списка
    PlayerNode *tail; // Указатель на конец списка

    // Конструктор по умолчанию
    PlayerList();

    // Деструктор для освобождения памяти
    ~PlayerList();

    // Добавление узла в конец списка
    void appendNode(const Player& value);

       // Оператор вывода узла в поток
    friend std::ostream &operator<<(std::ostream &os, const PlayerList &list);

    [[nodiscard]] Player *findById(int playerId) const;

    static void printPlayer(const PlayerList &list);
};

#endif //PROGA_KURS_PLAYERLIST_H
