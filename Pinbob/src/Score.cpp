#include "Score.h"
using namespace std;

<<<<<<< HEAD
Score::Score() :
=======
Score::Score() : 
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
	perfectCount(0), wellDoneCount(0), goodCount(0),
	badCount(0), missedCount(0){
		combo.push(0);
}
<<<<<<< HEAD

=======
	
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
void Score::clearScore(){
	perfectCount = 0;
	wellDoneCount = 0;
	goodCount = 0;
	badCount = 0;
	missedCount = 0;
}

void Score::setCombo(bool isCombo){
<<<<<<< HEAD
	if (isCombo){
=======
	if (isCombo){		
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
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
	setCombo(true);
}

void Score::wellDoneHit(){
	wellDoneCount++;
	setCombo(true);
}

void Score::goodHit(){
	goodCount++;
	setCombo(true);
}

void Score::badHit(){
	badCount++;
	setCombo(false);
}

void Score::missedHit(){
	missedCount++;
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
<<<<<<< HEAD
	return perfectCount * 5 + wellDoneCount * 3 + goodCount * 1
=======
	return perfectCount * 5 + wellDoneCount * 3 + goodCount * 1 
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
			- missedCount * 1;
}
