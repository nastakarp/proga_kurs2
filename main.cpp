#include <iostream>
#include <fstream>

#include <iomanip>
#include "model/core/Player.h"

#include "model/list/StringList.h"
#include "model/list/IntList.h"
#include "model/list/PlayerList.h"

using namespace std;

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
    return strcmp(*(player.statList->head->data.teamName), teamName) == 0;
}

//2 список игроков и кандидатов, которые играли ранее в одних командах
void printPlayersInTeams(PlayerList *playerList, StringList *teamNameList) {
    std::ofstream outputFile("output2.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file";
        return;
    }
    auto teamNameNode = teamNameList->head;
    //TeamNode *currentTeamNode = teamList->head;
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
void printPlayerCards(PlayerList *playerList) {
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

    // Сортировка игроков по общему числу игр
    sortPlayers(playerList, compareByAssists);

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

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream player_input("player.txt", std::ios::in);
    if (!player_input.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    StringList fullnameList;
    IntList dateOfBirthList;
    StringList cityList;
    StringList positionList;
    StringList statusList;

    PlayerList playerList;

    while (!player_input.eof()) {
        int id = charToInt(readUntilComma(player_input));

        char *fullname = readUntilComma(player_input);
        auto nameNode = fullnameList.append(fullname);

        int year = extractYear(readUntilComma(player_input));
        dateOfBirthList.append(year);

        char *city = readUntilComma(player_input);
        auto cityNode = cityList.append(city);

        char *position = readUntilComma(player_input);
        auto positionNode = positionList.append(position);

        char *status = readUntilComma(player_input);
        auto statusNode = statusList.append(status);

        Player player = Player(id, &nameNode->data, year, &cityNode->data, &positionNode->data, &statusNode->data);
        playerList.appendNode(player);
    }
    player_input.close();


    std::ifstream team_input("team.txt");
    if (!team_input.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 0;
    }

    StringList teamNameList;

    while (!team_input.eof()) {
        int playerId = charToInt(readUntilComma(team_input));
        char *teamName = readUntilComma(team_input);
        int playedMatches = charToInt(readUntilComma(team_input));      // Сыгранные матчи
        int goalsScored = charToInt(readUntilComma(team_input));        // Забитые голы
        int goalsConceded = charToInt(readUntilComma(team_input));      // Пропущенные голы
        int assists = charToInt(readUntilComma(team_input));            // Голевые передачи

        auto teamNameNode = teamNameList.append(teamName);
        //cout << teamName << endl;

        TeamStat teamStat(&teamNameNode->data, playedMatches, goalsScored, goalsConceded, assists);
        //cout << teamStat << endl;
        Player *player = playerList.findById(playerId);
        if (player != nullptr) {
            player->appendTeamStat(teamStat);
        }

    }

    //cout << playerList << endl;

    //1 игроков, сгруппированные по позиции и возрастной категории
    printPlayersGroupedByPositionAndAgeCategory(&positionList, &dateOfBirthList, &playerList);
    //2 список игроков и кандидатов, которые играли ранее в одних командах
    printPlayersInTeams(&playerList, &teamNameList);
    //3 учетные карточки на каждого игрока, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за все команды,
    printPlayerCards(&playerList);
    //4 учетные карточки на каждого игрока команды, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за команду
    //printPlayerCardsByTeam(&playerList, &teamNameList);

    return 0;
}
