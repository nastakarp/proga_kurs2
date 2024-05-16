#include <iostream>
#include <fstream>

#include "model/core/Player.h"

#include "model/list/StringList.h"
#include "model/list/IntList.h"
#include "model/list/PlayerList.h"
#include "Functional.h"

using namespace std;

void
readPlayersFromFile(PlayerList &playerList, StringList &fullnameList, IntList &dateOfBirthList, StringList &cityList,
                    StringList &positionList, StringList &statusList) {
    ifstream player_input("player.txt", std::ios::in);
    if (!player_input.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

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

}

void readTeamsFromFile(PlayerList &playerList, StringList &teamNameList) {

    std::ifstream team_input("team.txt");
    if (!team_input.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
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
}

void menu(PlayerList &playerList, StringList &positionList, StringList &teamNameList, IntList &dateOfBirthList,
          std::ofstream &output_activity) {
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
                output_activity << "(1) сформирован список игроков, сгруппированный по позиции и возрастной категории"
                                << std::endl;
                break;
            case 2:
                printPlayersInTeams(&playerList, &teamNameList);
                output_activity << "(2) сформирован список игроков и кандидатов, которые играли ранее в одних командах"
                                << std::endl;
                break;
            case 3:
                int choice3;
                do {
                    // Отобразить опции для выбора
                    std::cout << "1. comparison of players by total number of matches" << std::endl;
                    std::cout << "2. comparison of players by total number of goals scored" << std::endl;
                    std::cout << "3. comparison of players by the total number of goals conceded" << std::endl;
                    std::cout << "4. comparison of players by total number of assists" << std::endl;

                    std::cout << "5. [Back to main menu]" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> choice3;
                    printPlayerCards(&playerList, choice3);
                    switch (choice3) {
                        case 1:
                            output_activity
                                    << "(3.1) сформированы учетные карточки на каждого игрока, упорядоченные по общему числу игр за все команды"
                                    << std::endl;
                            break;
                        case 2:
                            output_activity
                                    << "(3.2) сформированы учетные карточки на каждого игрока, упорядоченные по общему числу забитых голов за все команды"
                                    << std::endl;
                            break;
                        case 3:
                            output_activity
                                    << "(3.3) сформированы учетные карточки на каждого игрока, упорядоченные по общему числу пропущенных голов за все команды"
                                    << std::endl;
                            break;
                        case 4:
                            output_activity
                                    << "(3.4) сформированы учетные карточки на каждого игрока, упорядоченные по общему числу голевых передач за все команды"
                                    << std::endl;
                            break;
                        case 5:
                            output_activity
                                    << "(3.5) возвращение к общему меню"
                                    << std::endl;
                            break;
                        default:
                            output_activity
                                    << "(3) Неправильный выбор. Попробуйте снова"
                                    << std::endl;
                            break;
                    }

                } while (choice3 != 5); // Повторять до тех пор, пока пользователь не выберет "Вернуться в главное меню"
                break;
            case 4:
                int choice4;
                do {
                    // Отобразить опции для выбора
                    std::cout << "1. comparison of players by total number of matches" << std::endl;
                    std::cout << "2. comparison of players by total number of goals scored" << std::endl;
                    std::cout << "3. comparison of players by the total number of goals conceded" << std::endl;
                    std::cout << "4. comparison of players by total number of assists" << std::endl;

                    std::cout << "5. [Back to main menu]" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> choice4;
                    printPlayerCardsByTeam(&playerList, &teamNameList, choice4);
                    switch (choice4) {
                        case 1:
                            output_activity
                                    << "(4.1) сформированы учетные карточки на каждого игрока команды, упорядоченные по общему числу игр за команду"
                                    << std::endl;
                            break;
                        case 2:
                            output_activity
                                    << "(4.2) сформированы учетные карточки на каждого игрока команды, упорядоченные по общему числу забитых голов за команду"
                                    << std::endl;
                            break;
                        case 3:
                            output_activity
                                    << "(4.3) сформированы учетные карточки на каждого игрока команды, упорядоченные по общему числу пропущенных голов за команду"
                                    << std::endl;
                            break;
                        case 4:
                            output_activity
                                    << "(4.4) сформированы учетные карточки на каждого игрока команды, упорядоченные по общему числу голевых передач за команду"
                                    << std::endl;
                            break;
                        case 5:
                            output_activity
                                    << "(4.5) возвращение к общему меню"
                                    << std::endl;
                            break;
                        default:
                            output_activity
                                    << "(4) Неправильный выбор. Попробуйте снова"
                                    << std::endl;
                            break;
                    }
                } while (choice4 != 5); // Повторять до тех пор, пока пользователь не выберет "Вернуться в главное меню"
                break;
                //printPlayerCardsByTeam(&playerList, &teamNameList);
            case 5:
                exitMenu = true;
                output_activity << "работа программы завершена" << std::endl;
                break;
            default:
                std::cout << "Wrong choice. Try again" << std::endl;
                output_activity << "Неправильный выбор. Попробуйте снова" << std::endl;
                break;
        }
    }
}

int main() {

    StringList fullnameList;
    IntList dateOfBirthList;
    StringList cityList;
    StringList positionList;
    StringList statusList;

    PlayerList playerList;

    StringList teamNameList;

    std::ofstream output_activity("output_activity.txt");
    if (!output_activity.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }
    readPlayersFromFile(playerList, fullnameList, dateOfBirthList, cityList, positionList, statusList);

    readTeamsFromFile(playerList, teamNameList);
    PlayerList::printPlayer(playerList);
    menu(playerList, positionList, teamNameList, dateOfBirthList, output_activity);

    return 0;
}
