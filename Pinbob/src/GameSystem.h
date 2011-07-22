/*
 * GameSystem.h
 *
 *  Created on: Jul 22, 2011
 *      Author: ovilia
 */

#ifndef GAMESYSTEM_H_
#define GAMESYSTEM_H_

#include "Menu.h"

enum StageName{ROOT_STAGE, MODE_STAGE, MUSIC_STAGE, DETECT_STAGE, GAME_STAGE,
				PAUSE_STAGE, GAMEOVER_STAGE};

class GameSystem{
public:
	GameSystem();

	void renderStage();//render main scene according to current stage
	StageName getStage();
	void setStage(StageName stage);

private:
	StageName curStage;

	static Menu mainMenu;
	static Menu modeMenu;
	static Menu musicMenu;
	static Menu ingameMenu;
};


#endif /* GAMESYSTEM_H_ */
