#ifndef UNTITLED_STRINGNODE_H
#define UNTITLED_STRINGNODE_H

#include "../../Util.h"

struct StringNode {
    char* data; // Указатель на данные
    StringNode* next; // Указатель на следующий узел

    // Конструктор
    explicit StringNode(const char* value);

    ~StringNode();
};

#endif //UNTITLED_STRINGNODE_H
