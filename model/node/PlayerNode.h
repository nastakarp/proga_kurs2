#ifndef PROGA_KURS_PLAYERNODE_H
#define PROGA_KURS_PLAYERNODE_H

#include <iostream>
#include "../core/Player.h"

struct PlayerNode {
    Player data; // Исправлено на Position
    PlayerNode *next; // Указатель на следующий узел

    // Конструктор для инициализации узла с заданным значением и указателем на следующий узел
    explicit PlayerNode(const Player& value);

    // Деструктор для освобождения ресурсов
    ~PlayerNode();

    // Оператор сравнения равенства PositionNode
    friend bool operator==(const PlayerNode &lhs, const PlayerNode &rhs);

    // Вывод узла в поток
    friend std::ostream &operator<<(std::ostream &os, const PlayerNode &node);
};

#endif //PROGA_KURS_POSITIONNODE_H

