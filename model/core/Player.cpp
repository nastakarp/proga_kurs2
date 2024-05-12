#include "Player.h"

Player::Player(
        int id,
        char **playerName,
        int playerYear,
        char **playerCity,
        char **playerPosition,
        char **playerStatus
) : idPlayer(id), name(playerName), year(playerYear),city(playerCity), position(playerPosition), status(playerStatus) {}

Player::~Player() = default;

void Player::appendTeamStat(const TeamStat& value) {
    this->statList.appendNode(value);
    commonPlayedMatches += value.playedMatches;      // Сыгранные матчи
    commonGoalsScored += value.goalsScored;          // Забитые голы
    commonGoalsConceded += value.goalsConceded;      // Пропущенные голы
    commonAssists += value.assists;                  // Голевые передачи
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << player.idPlayer << " ";
    os << *(player.name) << " ";
    os << player.year << " ";
    os << *(player.city) << " ";
    os << *(player.position) << " ";
    os << *(player.status) << " ";
    os << player.commonPlayedMatches << " ";
    return os;
}

bool operator==(const Player &lhs, const Player &rhs) {
    // Сравниваем все поля структуры Player
    return lhs.idPlayer == rhs.idPlayer;
}
