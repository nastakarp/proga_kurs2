#ifndef UNTITLED_INTNODE_H
#define UNTITLED_INTNODE_H

struct IntNode {
    int data; // Данные узла
    IntNode* next; // Указатель на следующий узел

    // Конструктор
    explicit IntNode(int value);

    // Деструктор
    ~IntNode();
};

#endif //UNTITLED_INTNODE_H
