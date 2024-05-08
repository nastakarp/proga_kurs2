#include "TeamStatList.h"

TeamStatList::TeamStatList() : head(nullptr), tail(nullptr) {}


// Деструктор для освобождения памяти
TeamStatList::~TeamStatList() {
    TeamStatNode *current = head; // Указатель на текущий узел

    while (current != nullptr) {
        TeamStatNode *next = current->next; // Сохраняем указатель на следующий узел
        delete current; // Освобождаем память для текущего узла
        current = next; // Переходим к следующему узлу
    }

    head = nullptr; // Устанавливаем указатель на начало списка в nullptr
    tail = nullptr; // Устанавливаем указатель на конец списка в nullptr
}

// Добавление узла в конец списка
void TeamStatList::appendNode(const TeamStat &value) {
    // Проверяем, существует ли уже такое значение в списке
    TeamStatNode *current = head;
    while (current != nullptr) {
        if (current->data == value) {
            // Значение уже присутствует в списке, поэтому выходим из функции
            return;
        }
        current = current->next;
    }
    // Создаем новый узел с заданным значением
    auto *newNode = new TeamStatNode(value);

    // Если список пуст, устанавливаем новый узел как начало и конец списка
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        // Добавляем новый узел в конец списка и обновляем указатель на хвост
        tail->next = newNode;
        tail = newNode;
    }
}

// Оператор вывода узла в поток
std::ostream &operator<<(std::ostream &os, const TeamStatList &list) {
    TeamStatNode *current = list.head;
    while (current != nullptr) {
        os << current->data << " -> ";
        current = current->next;
    }
    os << "NULL";
    return os;
}
