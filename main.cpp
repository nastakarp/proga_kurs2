#include <iostream>
#include <fstream>

#include "model/core/Player.h"

#include "model/list/StringList.h"
#include "model/list/IntList.h"
#include "model/list/PlayerList.h"

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

        char* city = readUntilComma(player_input);
        auto cityNode = cityList.append(city);

        char* position = readUntilComma(player_input);
        auto positionNode = positionList.append(position);

        char* status = readUntilComma(player_input);
        auto statusNode = statusList.append(status);

        Player player = Player(id, &nameNode->data, &cityNode->data, &positionNode->data, &statusNode->data);
        playerList.appendNode(player);
    }

    cout << endl;
    cout << playerList << endl;

    player_input.close();
    return 0;
}
