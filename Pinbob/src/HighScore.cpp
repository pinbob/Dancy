#include "HighScore.h"
#include <fstream>
#include <time.h>
using namespace std;

HighScore::HighScore() : MAX_AMT(10), FILE_NAME("asset/conf/.highScore"){
	readFile();
}

HighScore::~HighScore(){
	delete score;
	delete scoreTime;
}

void HighScore::reset(){
	printf("Reseting...\n");
	//Reset file
	fstream infile(FILE_NAME, fstream::in | fstream::trunc);
	infile.close();

	//Reset variables
	scoreAmt = 0;
	for (int i = 0; i < MAX_AMT; ++i){
		score[i] = 0;
		scoreTime[i] = 0;
	}
}

int HighScore::getScoreAmt(){
	return scoreAmt;
}

int HighScore::getScore(int index){
	return score[index];
}

int HighScore::getTime(int index){
	return scoreTime[index];
}

int HighScore::judgeScore(int newScore){ 
	if (newScore <= 0){//Cannot add
		return -1;
	}
	for (int i = 0; i < MAX_AMT; ++i){
		//If bigger than any, add to it
		if (newScore > score[i]){
			//If originally is less than MAX_AMT, amt++
			if (scoreAmt < MAX_AMT){
				scoreAmt++;
			}

			//Move one space backward
			for (int j = MAX_AMT - 1; j > i; --j){
				score[j] = score[j - 1];
				scoreTime[j] = scoreTime[j - 1];
			}
			score[i] = newScore;
			scoreTime[i] = time(NULL);//Get current time

			//Write into file
			writeFile();

			//Return index of score
			return i;
		}
	}
	//Not large enough
	return -1;
}

bool HighScore::readFile(){
	scoreAmt = 0;
	score = new int[MAX_AMT];
	scoreTime = new time_t[MAX_AMT];

	ifstream infile(FILE_NAME, fstream::binary);
	
	//Get file length
	infile.seekg(0, ios::end);
	int length = infile.tellg();
	infile.seekg(0, ios::beg);

	//If length cannot mod, file is modified unexpectedly,
	//reset it!
	if (length % (sizeof(int) * 3) != 0){
		printf("length error: length = %d\n", length);
		reset();
		return false;
	}else{
		scoreAmt = length / (sizeof(int) * 3);
	}
	
	//Read in information, make sure it is not modified
	for (int i = 0; i < MAX_AMT; ++i){
		if (i < scoreAmt){
			infile.read((char*)&score[i], sizeof(int));
			infile.read((char*)&scoreTime[i], sizeof(time_t));

			//Judge if modified
			int flag;
			infile.read((char*)&flag, sizeof(int));
			if (flag != (score[i] ^ scoreTime[i])){
				printf("flag error: flag[%d] = %d, xor = %d\n", i, flag, score[i] ^ scoreTime[i]);
				reset();
				return false;
			}
		}else{
			score[i] = 0;
			scoreTime[i] = 0;
		}
	}
	infile.close();
	return true;
}

void HighScore::writeFile(){
	ofstream outfile(FILE_NAME, ios::binary);
	for (int i = 0; i < scoreAmt; ++i){
		outfile.write((char*)&score[i], sizeof(int));
		outfile.write((char*)&scoreTime[i], sizeof(time_t));
		int flag = score[i] ^ scoreTime[i];
		outfile.write((char*)&flag, sizeof(int));
	}
	outfile.close();
}
