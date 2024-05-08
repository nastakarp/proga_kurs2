#ifndef PROGA_KURS_PLAYER_H
#define PROGA_KURS_PLAYER_H

#include "../list/TeamStatList.h"

struct Player {

    Player(int id, char **playerName, char **playerCity, char **playerPosition, char **playerStatus);

    int idPlayer;
    char **name;
    char **city;
    char **position;
    char **status;
    TeamStatList statList;

    ~Player();

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    friend bool operator==(const Player &lhs, const Player &rhs);

};

#endif //PROGA_KURS_PLAYER_H

