#include <iostream>
#include <fstream>

#include "model/core/Player.h"

#include "model/list/StringList.h"
#include "model/list/IntList.h"
#include "model/list/PlayerList.h"
#include "Functional.h"

using namespace std;

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

    int choice;
    bool exitMenu = false;

    while (!exitMenu) {
        // Выводим меню
        std::cout << "Select a function:" << std::endl;
        //1 игроков, сгруппированные по позиции и возрастной категории
        std::cout << "1. list of players grouped by position and age category" << std::endl;
        //2 список игроков и кандидатов, которые играли ранее в одних командах
        std::cout << "2. list of players and candidates who have previously played in the same teams" << std::endl;
        //3 учетные карточки на каждого игрока, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за все команды,
        std::cout
                << "3. scorecards for each player, ordered (separately) by the total number of games, goals and assists for all teams"
                << std::endl;
        //4 учетные карточки на каждого игрока команды, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за команду
        std::cout
                << "4. registration cards for each player of the team, ordered (separately) by the total number of games, goals and assists for the team"
                << std::endl;
        std::cout << "5. exit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        // Обрабатываем выбор пользователя
        switch (choice) {
            case 1:
                printPlayersGroupedByPositionAndAgeCategory(&positionList, &dateOfBirthList, &playerList);
                break;
            case 2:
                printPlayersInTeams(&playerList, &teamNameList);
                break;
            case 3:
                printPlayerCards(&playerList);
                break;
            case 4:
                printPlayerCardsByTeam(&playerList, &teamNameList);
                break;
            case 5:
                exitMenu = true;
                break;
            default:
                std::cout << "Wrong choice. Try again" << std::endl;
                break;
        }
    }
    return 0;
}
