/*
 * Score.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Zhang Wenli
 */

#include "Score.h"
using namespace std;

Score::Score() :
	perfectCount(0), wellDoneCount(0), goodCount(0),
	badCount(0), missedCount(0),score(0){
		combo.push(0);
}

void Score::clearScore(){
	perfectCount = 0;
	wellDoneCount = 0;
	goodCount = 0;
	badCount = 0;
	missedCount = 0;
}

void Score::setCombo(bool isCombo){
	if (isCombo){
		//top combo may be 0 to more, add one to them
		combo.top()++;
	}else{
		//if top combo is 0, do nothing
		//else, push 0 to top
		if (combo.top() != 0){
			combo.push(0);
		}
	}
}

unsigned int Score::getCombo(){
	return combo.top();
}

void Score::perfectHit(){
	perfectCount++;
	score += 10;
	setCombo(true);
}

void Score::wellDoneHit(){
	wellDoneCount++;
	score += 8;
	setCombo(true);
}

void Score::goodHit(){
	goodCount++;
	score += 5;
	setCombo(true);
}

void Score::badHit(){
	badCount++;
	score += 2;
	setCombo(false);
}

void Score::missedHit(){
	missedCount++;
	if (score > 0) {
		score -= 1;
	}
	setCombo(false);
}

unsigned int Score::getPerfectCount(){
	return perfectCount;
}

unsigned int Score::getWellDoneCount(){
	return wellDoneCount;
}

unsigned int Score::getGoodCount(){
	return goodCount;
}

unsigned int Score::getBadCount(){
	return badCount;
}

unsigned int Score::getMissedCount(){
	return missedCount;
}

unsigned int Score::getScore(){
	return score;
}
