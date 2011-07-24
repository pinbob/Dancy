/*
 * GameSystem.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: ovilia
 */

#include "GameSystem.h"
#include <string>
using namespace std;

GameSystem::GameSystem(){
	curStage = ROOT_STAGE;

	/*** Init static menu ***/
	string mainPath[] = {
		"asset/images/startGame.png",
		"asset/images/options.png",
		"asset/images/highScore.png",
		"asset/images/credits.png",
		"asset/images/quit.png"};
	mainMenu = Menu(5, mainPath);

	string modePath[] = {
		"asset/images/classical.png"
	};
	modeMenu = Menu(1, modePath);

	string musicPath[] = {
		"asset/images/music1.png",
		"asset/images/music2.png",
		"asset/images/music3.png"
	};
	musicMenu = Menu(3, musicPath);

	string ingameMenu[] = {
		"asset/images/continue.png",
		"asset/images/restart.png",
		"asset/images/quit.png"
	};
	ingameMenu = Menu(3, ingameMenu);
}

void GameSystem::renderStage(){
	//TODO
	switch(curStage){
	case ROOT_STAGE:
		//render root stage
		break;
	case MODE_STAGE:
		break;
	case MUSIC_STAGE:
		break;
	case DETECT_STAGE:
		break;
	case GAME_STAGE:
		break;
	case PAUSE_STAGE:
		break;
	case GAMEOVER_STAGE:
		break;
	}
}

StageName GameSystem::getStage(){
	return curStage;
}

void GameSystem::setStage(StageName stage){
	curStage = stage;
}
