#include <iostream>
#include "TeamStat.h"

// Конструктор
TeamStat::TeamStat(char **teamName, int matches, int scored, int conceded, int assist) :
        teamName(teamName),
        playedMatches(matches),
        goalsScored(scored),
        goalsConceded(conceded),
        assists(assist) {}

// Деструктор
TeamStat::~TeamStat() {
    delete[]teamName;
}

std::ostream &operator<<(std::ostream &os, const TeamStat &stat) {
    os << stat.teamName << " " << stat.playedMatches << " " << stat.goalsScored << " " << stat.goalsConceded << " "
       << stat.assists;
    return os;
}

bool operator==(const TeamStat &name1, const TeamStat &name2) {
    return strcmp(*name1.teamName, *name2.teamName) == 0;
}
