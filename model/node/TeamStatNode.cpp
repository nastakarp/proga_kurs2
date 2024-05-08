#include "TeamStatNode.h"

// Конструктор для инициализации узла с заданным значением и указателем на следующий узел
TeamStatNode::TeamStatNode(const TeamStat& value) : data(value), next(nullptr) {}

// Деструктор для освобождения ресурсов
TeamStatNode::~TeamStatNode() = default;

// Оператор сравнения равенства NameNode
bool operator==(const TeamStatNode &lhs, const TeamStatNode &rhs) {
    // Сравниваем данные игроков
    return lhs.data == rhs.data;
}

// Вывод узла в поток
std::ostream &operator<<(std::ostream &os, const TeamStatNode &node) {
    os << node.data;
    return os;
}
