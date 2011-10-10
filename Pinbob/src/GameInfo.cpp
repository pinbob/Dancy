/*
 * GameInfo.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: yejiabin
 */

#include "GameInfo.h"

GameInfo::GameInfo() :
		score(new Score) {

}

GameInfo::~GameInfo() {
	delete score;
}

Score *GameInfo::getScore() const {
	return score;
}

void GameInfo::setScore(Score *score) {
	this->score = score;
}

std::string GameInfo::getPlayerName() const {
	return playerName;
}

void GameInfo::setPlayerName(std::string playerName) {
	this->playerName = playerName;
}

void GameInfo::clearScore() {
	if (this->score) {
		delete score;
	}
	this->score = new Score();
}

