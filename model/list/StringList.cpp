#include "StringList.h"

// Конструктор по умолчанию
StringList::StringList() : head(nullptr), tail(nullptr) {}

// Деструктор
StringList::~StringList() {
    // Удаление всех узлов списка
    StringNode *current = head;
    while (current != nullptr) {
        StringNode *temp = current;
        current = current->next;
        delete temp;
    }
}

// Добавление элемента в конец списка, если его там нет
StringNode *StringList::append(const char *value) {
    // Проверка наличия элемента в списке
    StringNode *current = head;
    while (current != nullptr) {
        if (strcmp(current->data, value) == 0) {
            // Элемент уже существует в списке, выходим из функции
            return current;
        }
        current = current->next;
    }

    // Создание нового узла
    auto* newNode = new StringNode(value);

    // Если список пуст или новый элемент меньше первого элемента, вставляем его в начало
    if (head == nullptr || strcmp(value, head->data) < 0) {
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head; // Если список был пуст, новый элемент также становится хвостом
        }
        return newNode;
    }

    // Поиск места для вставки нового элемента
    current = head;
    while (current->next != nullptr && strcmp(value, current->next->data) > 0) {
        current = current->next;
    }

    // Вставка нового элемента после текущего узла
    newNode->next = current->next;
    current->next = newNode;

    // Если новый элемент добавлен в конец списка, обновляем указатель на хвост
    if (current == tail) {
        tail = newNode;
    }
    return newNode;
}

// Перегрузка оператора вывода для вывода списка в поток
std::ostream& operator<<(std::ostream& os, const StringList& list) {
    StringNode* current = list.head;
    while (current != nullptr) {
        os << current->data;
        if (current->next != nullptr) {
            os << "\t"; // Выводим табуляцию между элементами списка
        }
        current = current->next;
    }
    return os;
}
void StringList::print(std::ofstream &output){
    StringNode* current = this->head;
    while (current != nullptr) {
        printString(output,current->data);
        if (current->next != nullptr) {
            output << "\t"; // Выводим табуляцию между элементами списка
        }
        current = current->next;
    }
}
