//
// Created by Анастасия on 01.05.2024.
//

#ifndef PROGA_KURS_PLAYER_H
#define PROGA_KURS_PLAYER_H

#include "../list/TeamStatList.h"

struct Player {

    Player(int id, char **playerName, int year, char **playerCity, char **playerPosition, char **playerStatus);

    int idPlayer;
    char **name;
    int year;
    char **city;
    char **position;
    char **status;

    TeamStatList statList;

    int commonPlayedMatches = 0;      // Сыгранные матчи
    int commonGoalsScored = 0;        // Забитые голы
    int commonGoalsConceded = 0;      // Пропущенные голы
    int commonAssists = 0;            // Голевые передачи

    void appendTeamStat(const TeamStat& value);

    ~Player();

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    friend bool operator==(const Player &lhs, const Player &rhs);

};

#endif //PROGA_KURS_PLAYER_H

