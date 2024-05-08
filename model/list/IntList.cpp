#include <ostream>
#include "IntList.h"

// Конструктор по умолчанию
IntList::IntList() : head(nullptr), tail(nullptr) {}

// Деструктор
IntList::~IntList() {
    // Удаление всех узлов списка
    IntNode *current = head;
    while (current != nullptr) {
        IntNode *temp = current;
        current = current->next;
        delete temp;
    }
}

// Добавление элемента в конец списка, если его там нет
void IntList::append(int value) {
    // Проверка наличия элемента в списке
    IntNode *current = head;
    while (current != nullptr) {
        if (current->data == value) {
            // Элемент уже существует в списке, выходим из функции
            return;
        }
        current = current->next;
    }

    // Создание нового узла
    auto* newNode = new IntNode(value);

    // Если список пуст или новый элемент меньше первого элемента, вставляем его в начало
    if (head == nullptr || value < head->data) {
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head; // Если список был пуст, новый элемент также становится хвостом
        }
        return;
    }

    // Поиск места для вставки нового элемента
    current = head;
    while (current->next != nullptr && value > current->next->data) {
        current = current->next;
    }

    // Вставка нового элемента после текущего узла
    newNode->next = current->next;
    current->next = newNode;

    // Если новый элемент добавлен в конец списка, обновляем указатель на хвост
    if (current == tail) {
        tail = newNode;
    }
}

// Перегрузка оператора вывода для вывода списка в поток
std::ostream& operator<<(std::ostream& os, const IntList& list) {
    IntNode* current = list.head;
    while (current != nullptr) {
        os << current->data;
        if (current->next != nullptr) {
            os << "\t"; // Выводим табуляцию между элементами списка
        }
        current = current->next;
    }
    return os;
}
