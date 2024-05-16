#include "PlayerList.h"

PlayerList::PlayerList() : head(nullptr), tail(nullptr) {}


// Деструктор для освобождения памяти
PlayerList::~PlayerList() {
    PlayerNode *current = head; // Указатель на текущий узел

    while (current != nullptr) {
        PlayerNode *next = current->next; // Сохраняем указатель на следующий узел
        delete current; // Освобождаем память для текущего узла
        current = next; // Переходим к следующему узлу
    }

    head = nullptr; // Устанавливаем указатель на начало списка в nullptr
    tail = nullptr; // Устанавливаем указатель на конец списка в nullptr
}

// Добавление узла в конец списка
void PlayerList::appendNode(const Player &value) {

    // Проверяем, существует ли уже такое значение в списке
    PlayerNode *current = head;
    while (current != nullptr) {
        if (current->data == value) {
            // Значение уже присутствует в списке, поэтому выходим из функции
            return;
        }
        current = current->next;
    }

    // Создаем новый узел с заданным значением
    auto *newNode = new PlayerNode(value);

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

Player *PlayerList::findById(int playerId) const {
    auto currentNode = this->head;
    // Начинаем с головы списка
    while (currentNode != nullptr) {
        if (currentNode->data.idPlayer == playerId) {
            return &(currentNode->data); // Возвращаем указатель на игрока, если найден
        }
        currentNode = currentNode->next; // Переходим к следующему узлу
    }
    return nullptr; // Если игрок с указанным идентификатором не найден, возвращаем nullptr
}

// Оператор вывода узла в поток
std::ostream &operator<<(std::ostream &os, const PlayerList &list) {
    PlayerNode *current = list.head;
    os<< "Head NULL-> ";
    while (current != nullptr) {
        os << current->data << " -> ";
        current = current->next;
    }
    os<<"NULL Tail\n" ;
    return os;
}

void PlayerList::printPlayer(const PlayerList &list) {
    std::ofstream output("output_player.txt");
    if (!output.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }
    PlayerNode *current = list.head;
    output << "Head NULL" << "\n";
    output << "--------------------------------------" << std::endl;
    output << " | /|\\" << "\n";
    output << "\\|/ |" << "\n";
    while (current != nullptr) {
        output << "--------------------------------------" << std::endl;
        output << "id:\t " << current->data.idPlayer << std::endl;
        output << "name:\t ";
        printString(output,*current->data.name);
        output<<std::endl;
        output << "year:\t " <<current->data.year << std::endl;
        output << "city:\t ";
        printString(output,*current->data.city);
        output<<std::endl;
        output << "position:\t ";
        printString(output,*current->data.position);
        output<<std::endl;
        output << "status:\t ";
        printString(output,*current->data.status);
        output<<std::endl;
        output << "teamName:\t ";

        Player currentPlayer = current->data;
        auto* statList = currentPlayer.statList;
        auto* teamNode = statList->head;

        while (teamNode != nullptr) {
            printString(output, *teamNode->data.teamName);
            output << " "; // Разделяем команды пробелом
            teamNode = teamNode->next;
        }
        //printString(output,*current->data.statList->head->data.teamName);
        output<<std::endl;
        output << "commonPlayedMatches:\t " <<current->data.commonPlayedMatches << std::endl;
        output << "commonGoalsScored:\t " <<current->data.commonGoalsScored << std::endl;
        output << "commonGoalsConceded:\t " <<current->data.commonGoalsConceded << std::endl;
        output << "commonAssists:\t " <<current->data.commonAssists << std::endl;
        output << "--------------------------------------" << std::endl;
        output << " | /|\\" << "\n";
        output << "\\|/ |" << "\n";
        current = current->next;
    }
    output << "--------------------------------------" << std::endl;
    output << "NULL Tail" << "\n";
}
