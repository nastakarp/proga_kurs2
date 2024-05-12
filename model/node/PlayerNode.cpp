#include "PlayerNode.h"

// Конструктор для инициализации узла с заданным значением и указателем на следующий узел
PlayerNode::PlayerNode(const Player &value) : data(value), next(nullptr) {}

// Деструктор для освобождения ресурсов
PlayerNode::~PlayerNode() = default;

// Оператор сравнения равенства NameNode
bool operator==(const PlayerNode &lhs, const PlayerNode &rhs) {
    // Сравниваем данные игроков
    return rhs.data.idPlayer == lhs.data.idPlayer;
}

// Вывод узла в поток
std::ostream &operator<<(std::ostream &os, const PlayerNode &node) {
    os << node.data.idPlayer << " " << *node.data.name;
    return os;
}
