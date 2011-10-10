/*
 * GameInfo.h
 *
 *  Created on: Jul 25, 2011
 *      Author: yejiabin
 */

#ifndef GAMEINFO_H_
#define GAMEINFO_H_

#include "Score.h"
#include <string>

class GameInfo {
public:
	GameInfo();
	virtual ~GameInfo();
    Score *getScore() const;
    void setScore(Score *score);
    std::string getPlayerName() const;
    void setPlayerName(std::string playerName);
    void clearScore();
private:
	Score* score;
	std::string playerName;
};

#endif /* GAMEINFO_H_ */
