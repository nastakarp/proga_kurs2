#ifndef PROGA_KURS_TEAMSTATNODE_H
#define PROGA_KURS_TEAMSTATNODE_H

#include "../core/TeamStat.h" // Подключаем заголовочный файл для структуры TeamName

struct TeamStatNode {
    TeamStat data;
    TeamStatNode *next;

    // Конструктор для инициализации узла с заданным значением и указателем на следующий узел
    explicit TeamStatNode(const TeamStat& value);

    // Деструктор для освобождения ресурсов
    ~TeamStatNode();
};

// Оператор сравнения равенства NameNode
bool operator==(const TeamStatNode &lhs, const TeamStatNode &rhs);

// Вывод узла в поток
std::ostream &operator<<(std::ostream &os, const TeamStatNode &node);


#endif //PROGA_KURS_TEAMSTATNODE_H
