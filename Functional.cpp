//
// Created by Анастасия on 12.05.2024.
//

#include <iomanip>
#include "Functional.h"
#include "model/list/StringList.h"
#include "model/list/IntList.h"
#include "model/list/PlayerList.h"

//1 игроков, сгруппированные по позиции и возрастной категории
void printPlayersGroupedByPositionAndAgeCategory(StringList *positionList, IntList *dateOfBirthList,
                                                 PlayerList *playerList) {
    std::ofstream outputFile("output1.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file";
        return;
    }

    auto positionNode = positionList->head;

    // Определим ширину каждого столбца
    int positionWidth = 15;
    int yearWidth = 8;
    int nameWidth = 25;

    // Флаг для отслеживания, была ли уже выведена позиция
    bool positionPrinted = false;

    // Заголовки таблицы
    outputFile << std::left << std::setw(positionWidth) << "Position" << std::setw(yearWidth) << "Year"
               << std::setw(nameWidth) << "Player"
               << std::endl;
    outputFile << std::setfill('-') << std::setw(positionWidth + yearWidth + nameWidth) << "" << std::setfill(' ')
               << std::endl;

    while (positionNode != nullptr) {
        auto dateOfBirthNode = dateOfBirthList->head;
        while (dateOfBirthNode != nullptr) {

            auto playerNode = playerList->head;
            while (playerNode != nullptr) {
                if ((*playerNode->data.position == positionNode->data) &&
                    (dateOfBirthNode->data == playerNode->data.year)) {
                    // Если позиция еще не была выведена, выводим ее
                    if (!positionPrinted) {
                        outputFile << std::left << std::setw(positionWidth) << positionNode->data
                                   << std::setw(yearWidth) << dateOfBirthNode->data
                                   << std::setw(nameWidth) << *(playerNode->data.name) << std::endl;
                        positionPrinted = true;
                    } else {
                        // Выводим только данные игрока
                        outputFile << std::left << std::setw(positionWidth) << ""
                                   << std::setw(yearWidth) << dateOfBirthNode->data
                                   << std::setw(nameWidth) << *(playerNode->data.name) << std::endl;
                    }
                }
                playerNode = playerNode->next;
            }
            dateOfBirthNode = dateOfBirthNode->next;
        }

        // Сбрасываем флаг для следующей позиции
        positionPrinted = false;
        positionNode = positionNode->next;
    }

    outputFile.close();
}

bool playedInTeam(const Player &player, const char *teamName) {
    auto *currentTeamNode = player.statList->head;
    while (currentTeamNode != nullptr) {
        if (strcmp(*currentTeamNode->data.teamName, teamName) == 0) {
            return true;
        }
        currentTeamNode = currentTeamNode->next;
    }
    return false;
}

//2 список игроков и кандидатов, которые играли ранее в одних командах
void printPlayersInTeams(PlayerList *playerList, StringList *teamNameList) {
    std::ofstream outputFile("output2.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file";
        return;
    }

    auto *teamNameNode = teamNameList->head;
    while (teamNameNode != nullptr) {
        outputFile << "Team: " << teamNameNode->data << std::endl;

        // Вывод игроков команды
        PlayerNode *currentPlayerNode = playerList->head;
        while (currentPlayerNode != nullptr) {
            if (playedInTeam(currentPlayerNode->data, teamNameNode->data)) {
                outputFile << *(currentPlayerNode->data.name) << std::endl;
            }
            currentPlayerNode = currentPlayerNode->next;
        }

        outputFile << "-------------------" << std::endl << std::endl;
        teamNameNode = teamNameNode->next;
    }


    outputFile.close();
}

// Функция для сравнения игроков по общему числу игр
bool compareByPlayedMatches(const Player &player1, const Player &player2) {
    return player1.commonPlayedMatches > player2.commonPlayedMatches;
}

// Функция для сравнения игроков по общему числу забитых голов
bool compareByGoalsScored(const Player &player1, const Player &player2) {
    return player1.commonGoalsScored > player2.commonGoalsScored;
}

// Функция для сравнения игроков по общему числу пропущенных голов
bool compareByGoalsConceded(const Player &player1, const Player &player2) {
    return player1.commonGoalsConceded > player2.commonGoalsConceded;
}

// Функция для сравнения игроков по общему числу голевых передач
bool compareByAssists(const Player &player1, const Player &player2) {
    return player1.commonAssists > player2.commonAssists;
}

void swapPlayerNode(PlayerNode *playerNode, PlayerNode *playerNode2) {
    // Обмен id игроков
    auto tempId = playerNode->data.idPlayer;
    playerNode->data.idPlayer = playerNode2->data.idPlayer;
    playerNode2->data.idPlayer = tempId;

    // Обмен имен игроков
    auto tempName = playerNode->data.name;
    playerNode->data.name = playerNode2->data.name;
    playerNode2->data.name = tempName;

    // Обмен года рождения
    auto tempYear = playerNode->data.year;
    playerNode->data.year = playerNode2->data.year;
    playerNode2->data.year = tempYear;

    // Обмен городов
    auto tempCity = playerNode->data.city;
    playerNode->data.city = playerNode2->data.city;
    playerNode2->data.city = tempCity;

    // Обмен позиций
    auto tempPosition = playerNode->data.position;
    playerNode->data.position = playerNode2->data.position;
    playerNode2->data.position = tempPosition;

    // Обмен статусов
    auto tempStatus = playerNode->data.status;
    playerNode->data.status = playerNode2->data.status;
    playerNode2->data.status = tempStatus;

    // Обмен сыгранных матчей
    auto tempPlayedMatches = playerNode->data.commonPlayedMatches;
    playerNode->data.commonPlayedMatches = playerNode2->data.commonPlayedMatches;
    playerNode2->data.commonPlayedMatches = tempPlayedMatches;

    // Обмен забитых голов
    auto tempGoalsScored = playerNode->data.commonGoalsScored;
    playerNode->data.commonGoalsScored = playerNode2->data.commonGoalsScored;
    playerNode2->data.commonGoalsScored = tempGoalsScored;

    // Обмен пропущенных голов
    auto tempGoalsConceded = playerNode->data.commonGoalsConceded;
    playerNode->data.commonGoalsConceded = playerNode2->data.commonGoalsConceded;
    playerNode2->data.commonGoalsConceded = tempGoalsConceded;

    // Обмен голевых передач
    auto tempAssists = playerNode->data.commonAssists;
    playerNode->data.commonAssists = playerNode2->data.commonAssists;
    playerNode2->data.commonAssists = tempAssists;

    // Обмен статистики команд
    auto tempStatList = playerNode->data.statList;
    playerNode->data.statList = playerNode2->data.statList;
    playerNode2->data.statList = tempStatList;
}

void sortPlayers(PlayerList *playerList, bool (*compare)(const Player &player1, const Player &player2)) {
    if (!playerList || !playerList->head || !compare)
        return;

    PlayerNode *current = playerList->head;
    while (current != nullptr) {
        PlayerNode *nextNode = current->next;
        while (nextNode != nullptr) {
            if (compare(nextNode->data, current->data)) {
                swapPlayerNode(current, nextNode);
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

//3 учетные карточки на каждого игрока, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за все команды,
void printPlayerCards(PlayerList *playerList, int choice) {
    std::ofstream outputFile("output3.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file";
        return;
    }

    // Определим ширину каждого столбца
    int nameWidth = 35;
    int size = 15;

    // Заголовки таблицы
    outputFile << std::left << std::setw(nameWidth) << "Player" << std::setw(size) << "Matches"
               << std::setw(size) << "Goals Scored" << std::setw(size) << "Goals Conceded"
               << std::setw(size) << "Assists" << std::endl;
    outputFile << std::setfill('-') << std::setw(nameWidth + 4 * size) << "" << std::setfill(' ') << std::endl;

    // Сортировка игроков

    switch (choice) {
        case 1:
            sortPlayers(playerList, compareByPlayedMatches);
            break;
        case 2:
            sortPlayers(playerList, compareByGoalsScored);
            break;
        case 3:
            sortPlayers(playerList, compareByGoalsConceded);
            break;
        case 4:
            sortPlayers(playerList, compareByAssists);
            break;
        case 5:
            break;
        default:
            std::cout << "Wrong choice. Try again" << std::endl;
            break;
    }

    // Вывод учетных карточек игроков
    PlayerNode *current = playerList->head;
    while (current != nullptr) {
        outputFile << std::left << std::setw(nameWidth) << *(current->data.name)
                   << std::setw(size) << current->data.commonPlayedMatches
                   << std::setw(size) << current->data.commonGoalsScored
                   << std::setw(size) << current->data.commonGoalsConceded
                   << std::setw(size) << current->data.commonAssists << std::endl;
        current = current->next;
    }

    outputFile << std::endl;
    outputFile.close();
}

bool compareBy_PlayedMatches(const Player &player1, const Player &player2, const char *teamName) {
    int player_1 = 0;
    int player_2 = 0;
    auto teamStatNode1 = player1.statList->head;
    while (teamStatNode1 != nullptr) {
        if (*teamStatNode1->data.teamName == teamName) {
            player_1 = teamStatNode1->data.playedMatches;
            break;
        }
        teamStatNode1=teamStatNode1->next;
    }
    auto teamStatNode2 = player2.statList->head;
    while (teamStatNode2 != nullptr) {
        if (*teamStatNode2->data.teamName == teamName) {
            player_2 = teamStatNode2->data.playedMatches;
            break;
        }
        teamStatNode2=teamStatNode2->next;
    }
    return player_1 > player_2;
}

bool compareBy_GoalsScored(const Player &player1, const Player &player2, const char *teamName) {
    int player_1 = 0;
    int player_2 = 0;
    auto teamStatNode1 = player1.statList->head;
    while (teamStatNode1 != nullptr) {
        if (*teamStatNode1->data.teamName == teamName) {
            player_1 = teamStatNode1->data.goalsScored;
            break;
        }
        teamStatNode1=teamStatNode1->next;
    }
    auto teamStatNode2 = player2.statList->head;
    while (teamStatNode2 != nullptr) {
        if (*teamStatNode2->data.teamName == teamName) {
            player_2 = teamStatNode2->data.goalsScored;
            break;
        }
        teamStatNode2=teamStatNode2->next;
    }
    return player_1 > player_2;
}

bool compareBy_GoalsConceded(const Player &player1, const Player &player2, const char *teamName) {
    int player_1 = 0;
    int player_2 = 0;
    auto teamStatNode1 = player1.statList->head;
    while (teamStatNode1 != nullptr) {
        if (*teamStatNode1->data.teamName == teamName) {
            player_1 = teamStatNode1->data.goalsConceded;
            break;
        }
        teamStatNode1=teamStatNode1->next;
    }
    auto teamStatNode2 = player2.statList->head;
    while (teamStatNode2 != nullptr) {
        if (*teamStatNode2->data.teamName == teamName) {
            player_2 = teamStatNode2->data.goalsConceded;
            break;
        }
        teamStatNode2=teamStatNode2->next;
    }
    return player_1 > player_2;
}

bool compareBy_Assists(const Player &player1, const Player &player2, const char *teamName) {
    int player_1 = 0;
    int player_2 = 0;
    auto teamStatNode1 = player1.statList->head;
    while (teamStatNode1 != nullptr) {
        if (*teamStatNode1->data.teamName == teamName) {
            player_1 = teamStatNode1->data.assists;
            break;
        }
        teamStatNode1=teamStatNode1->next;
    }
    auto teamStatNode2 = player2.statList->head;
    while (teamStatNode2 != nullptr) {
        if (*teamStatNode2->data.teamName == teamName) {
            player_2 = teamStatNode2->data.assists;
            break;
        }
        teamStatNode2=teamStatNode2->next;
    }
    return player_1 > player_2;
}

void sortPlayersByTeamName(
        PlayerList *playerList,
        const char* teamName,
        bool (*compare)(const Player &player1, const Player &player2, const char *teamName)){

    if (!playerList || !playerList->head || !compare)
        return;

    PlayerNode *current = playerList->head;
    while (current != nullptr) {
        PlayerNode *nextNode = current->next;
        while (nextNode != nullptr) {
            if (compare(nextNode->data, current->data,teamName)) {
                swapPlayerNode(current, nextNode);
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }

}

//4 учетные карточки на каждого игрока команды, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за команду
// Предполагается, что PlayerList, StringList, PlayerNode и другие структуры данных уже определены

void sortPlayersByChoice(PlayerList* playerList, const char* teamName, int choice) {
    switch (choice) {
        case 1:
            sortPlayersByTeamName(playerList, teamName, compareBy_PlayedMatches);
            break;
        case 2:
            sortPlayersByTeamName(playerList, teamName, compareBy_GoalsScored);
            break;
        case 3:
            sortPlayersByTeamName(playerList, teamName, compareBy_GoalsConceded);
            break;
        case 4:
            sortPlayersByTeamName(playerList, teamName, compareBy_Assists);
            break;
        case 5:
            break;
        default:
            std::cerr << "Wrong choice. Try again" << std::endl;
            break;
    }
}

void printPlayerStats(std::ofstream& outputFile, PlayerNode* current, const char *teamName, int nameWidth, int size) {
    while (current != nullptr) {
        if (playedInTeam(current->data, teamName)) {
            auto teamStatNode = current->data.statList->head;
            while (teamStatNode != nullptr) {
                if (*teamStatNode->data.teamName == teamName) {
                    outputFile << std::left << std::setw(nameWidth) << *(current->data.name)
                               << std::setw(size) << teamStatNode->data.playedMatches
                               << std::setw(size) << teamStatNode->data.goalsScored
                               << std::setw(size) << teamStatNode->data.goalsConceded
                               << std::setw(size) << teamStatNode->data.assists << std::endl;
                }
                teamStatNode = teamStatNode->next;
            }
        }
        current = current->next;
    }
}

void printPlayerCardsByTeam(PlayerList* playerList, StringList* teamNameList, int choice) {
    if (!playerList || !playerList->head) {
        std::cerr << "Player list is empty!" << std::endl;
        return;
    }

    std::ofstream outputFile("output4.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file" << std::endl;
        return;
    }

    int nameWidth = 35;
    int size = 15;

    auto teamNameNode = teamNameList->head;
    while (teamNameNode != nullptr) {
        // Вывод учетных карточек игроков по команде
        outputFile << "Player Cards for Team: " << teamNameNode->data << std::endl;
        outputFile << std::left << std::setw(nameWidth) << "Player"
                   << std::setw(size) << "Matches"
                   << std::setw(size) << "GoalsScored"
                   << std::setw(size) << "GoalsConceded"
                   << std::setw(size) << "Assists" << std::endl;

        sortPlayersByChoice(playerList, teamNameNode->data, choice);

        PlayerNode* current = playerList->head;
        printPlayerStats(outputFile, current, teamNameNode->data, nameWidth, size);

        teamNameNode = teamNameNode->next;
        outputFile << "--------------------------------------" << std::endl;
    }

    outputFile.close();
}
