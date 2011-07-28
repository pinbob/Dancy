/*
 * Score.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Zhang Wenli
 */

#ifndef SCORE_H
#define SCORE_H

#include <stack>
using namespace std;

class Score{
public:
	Score();
	void clearScore();

	/*Call ...Hit() everytime user click an arrow */
	void perfectHit();
	void wellDoneHit();
	void goodHit();
	void badHit();
	void missedHit();

	/* These five functions will call setCombo automatically.
	 * The first three setCombo(true),
	 * later two setCombo(false)
	 */
	unsigned int getPerfectCount();
	unsigned int getWellDoneCount();
	unsigned int getGoodCount();
	unsigned int getBadCount();
	unsigned int getMissedCount();

	/* return current score, return 0 if smaller than 0 */
	unsigned int getScore();

	/* return last combo amt */
	unsigned int getCombo();

private:
	unsigned int perfectCount;
	unsigned int wellDoneCount;
	unsigned int goodCount;
	unsigned int badCount;
	unsigned int missedCount;

	unsigned int score;

	stack<unsigned int> combo;

	void setCombo(bool isCombo);
};

#endif
