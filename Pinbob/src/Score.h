<<<<<<< HEAD
/*
 * Score.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Zhang Wenli
 */

=======
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
#ifndef SCORE_H
#define SCORE_H

#include <stack>
using namespace std;

class Score{
public:
	Score();
	void clearScore();
<<<<<<< HEAD

=======
	
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
	/*Call ...Hit() everytime user click an arrow */
	void perfectHit();
	void wellDoneHit();
	void goodHit();
	void badHit();
	void missedHit();
<<<<<<< HEAD

=======
	
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
	/* These five functions will call setCombo automatically.
	 * The first three setCombo(true),
	 * later two setCombo(false)
	 */
	unsigned int getPerfectCount();
	unsigned int getWellDoneCount();
	unsigned int getGoodCount();
	unsigned int getBadCount();
	unsigned int getMissedCount();
<<<<<<< HEAD

	/* return current score, return 0 if smaller than 0 */
	unsigned int getScore();

	/* return last combo amt */
	unsigned int getCombo();

=======
	
	/* return current score, return 0 if smaller than 0 */
	unsigned int getScore();
	
	/* return last combo amt */
	unsigned int getCombo();
	
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
private:
	unsigned int perfectCount;
	unsigned int wellDoneCount;
	unsigned int goodCount;
	unsigned int badCount;
	unsigned int missedCount;
<<<<<<< HEAD

	stack<unsigned int> combo;

=======
	
	stack<unsigned int> combo;
	
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
	void setCombo(bool isCombo);
};

#endif
