#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <time.h>

class HighScore{
public:
	//Read file and init HighScore variables
	HighScore();
	
	//Reset file and variables
	void reset();

	//Return amount of stored high scores
	int getScoreAmt();
	//Return score of the index
	int getScore(int index);
	//Return time of the index
	int getTime(int index);

	//Judge if score can be include in high score,
	//If so, return the index;
	//else, return -1
	int judgeScore(int newScore);

private:
	int MAX_AMT;
	char* FILE_NAME;

	//Amt of stored high score
	int scoreAmt;
	//Score of stored high score, from big to small
	int* score;
	//Time of stored high score, if scores are the same, newer time is in the front
	time_t* scoreTime;

	//Read in a encrypted high score file.
	//If it is modified unexpectedly, reset it and return false
	bool readFile();
	//Write file with encryption.
	//If error occurs, return false
	void writeFile();
	
};

#endif
