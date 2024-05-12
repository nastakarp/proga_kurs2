//
// Created by Анастасия on 12.05.2024.
//

#ifndef UNTITLED_FUNCTIONAL_H
#define UNTITLED_FUNCTIONAL_H

#include "model/list/StringList.h"
#include "model/list/IntList.h"
#include "model/list/PlayerList.h"

//1 игроков, сгруппированные по позиции и возрастной категории
void printPlayersGroupedByPositionAndAgeCategory(StringList *positionList, IntList *dateOfBirthList,
                                                 PlayerList *playerList);

//2 список игроков и кандидатов, которые играли ранее в одних командах
void printPlayersInTeams(PlayerList *playerList, StringList *teamNameList);

//3 учетные карточки на каждого игрока, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за все команды,
void printPlayerCards(PlayerList *playerList, int choice);

//4 учетные карточки на каждого игрока команды, упорядоченные (отдельно) по общему числу игр, голов и голевых передач за команду
void printPlayerCardsByTeam(PlayerList *playerList, StringList *teamNameList, int choice);

#endif //UNTITLED_FUNCTIONAL_H
