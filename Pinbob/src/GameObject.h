/*
 * GameObject.h
 *
 *  Created on: Jul 24, 2011
 *      Author: yejiabin
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "IState.h"
#include "DefaultGameLogic.h"
#include "Config.h"
#include "GameEventReceiver.h"
#include "GameInfo.h"
#include "../include/conio.h"
#include "irrKlang.h"
#include "NotesLoader.h"
#include "NoteData.h"
#include "Song.h"

struct GameMenuConfig {
	core::position2d<s32> position;
	core::rect<s32> size;
	const char* filename;
};

enum GAME_MENUS {
	MENU,
	UP_LEFT_AREA,
	DOWN_LEFT_AREA,
	UP_RIGHT_AREA,
	DOWN_RIGHT_AREA,
	UP_LEFT_AREA_PRESSED,
	DOWN_LEFT_AREA_PRESSED,
	UP_RIGHT_AREA_PRESSED,
	DOWN_RIGHT_AREA_PRESSED,
	GAME_MENU_LENGTH
};

const GameMenuConfig GAME_MENU_CONFIG[GAME_MENU_LENGTH] = {
    {position2d<s32>((SCREEN_WIDTH - MENU_WIDTH) / 2, SCREEN_HEIGHT - MENU_HEIGHT), 
            rect<s32>(0, 0, MENU_WIDTH, MENU_HEIGHT), "asset/images/menu.png" }, 
    {position2d<s32>(0, SCREEN_HEIGHT / 2 - ARROW_HEIGHT), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/ulArea.png" }, 
    {position2d<s32>(0, SCREEN_HEIGHT / 2), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/dlArea.png" }, 
    {position2d<s32>(SCREEN_WIDTH - ARROW_WIDTH, SCREEN_HEIGHT / 2 - ARROW_HEIGHT), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/urArea.png" }, 
    {position2d<s32>(SCREEN_WIDTH - ARROW_WIDTH, SCREEN_HEIGHT / 2), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/drArea.png" },
    {position2d<s32>(0, SCREEN_HEIGHT / 2 - ARROW_HEIGHT), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/ulArea1.png" }, 
    {position2d<s32>(0, SCREEN_HEIGHT / 2), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/dlArea1.png" }, 
    {position2d<s32>(SCREEN_WIDTH - ARROW_WIDTH, SCREEN_HEIGHT / 2 - ARROW_HEIGHT), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/urArea1.png" }, 
    {position2d<s32>(SCREEN_WIDTH - ARROW_WIDTH, SCREEN_HEIGHT / 2), 
            rect<s32>(0, 0, ARROW_WIDTH, ARROW_HEIGHT), "asset/images/drArea1.png" }
};

enum PauseMenu {
	GP_CONTINUE, GP_MAIN_MENU, GP_RESTART, GP_MENU_HEAD, GP_LENGTH
};

struct ResourceLayout {
	const char* filename;
	vector2d<s32> position;
};

enum IN_GAME_SUBSTATE {
	IG_DETECT, IG_UPDATE, IG_PAUSE, IG_GAMEOVER
};

const ResourceLayout GP_LAYOUT[GP_LENGTH] = {
    {"asset/images/GP_continue.png", 
            vector2d<s32>((SCREEN_WIDTH - GP_WIDTH) / 2, 
            (SCREEN_HEIGHT - GP_HEIGHT * GP_AMT - GP_TITLE_HEIGHT) / 2 + GP_TITLE_HEIGHT)}, 
    {"asset/images/GP_mainMenu.png", 
            vector2d<s32>((SCREEN_WIDTH - GP_WIDTH) / 2, 
            (SCREEN_HEIGHT - GP_HEIGHT * GP_AMT - GP_TITLE_HEIGHT) / 2 + GP_TITLE_HEIGHT + GP_HEIGHT)}, 
    {"asset/images/GP_restart.png", 
            vector2d<s32>((SCREEN_WIDTH - GP_WIDTH) / 2, 
            (SCREEN_HEIGHT - GP_HEIGHT * GP_AMT - GP_TITLE_HEIGHT) / 2 + GP_TITLE_HEIGHT + 2 * GP_HEIGHT)}, 
    {"asset/images/GP.png", 
            vector2d<s32>((SCREEN_WIDTH - GP_WIDTH) / 2,
            (SCREEN_HEIGHT - GP_HEIGHT * GP_AMT - GP_TITLE_HEIGHT) / 2)}};

class GameObject: public IState {
public:
	GameObject(IrrlichtDevice* pDevice, StateMachine* pStateMachine,
			u32 startTime);
	virtual void activate(IState* pPrevious);
	/* This method is called by the state machine on state deactivation. Must be implemented in subclass
	 * @param pNext the next active state */
	virtual void deactivate(IState* pNext);
	/*  This method is called by the state manager on each form.
	 *  @return "0" is no state change is wanted, "index of new state-1" to switch to another state, out of bounds index to quit program */
	virtual u32 update(void);
	virtual ~GameObject();
	void setCurrentSong(Song* song) {
		this->currentSong = song;
	}
//	void setCurrentSong(const char* song){
//		// the song name seems always contains \r
//		if (song[strlen(song)-1] == '\r') {
//			currentSong = new char[strlen(song)];
//			strncpy(currentSong, song, strlen(song)-1);
//			currentSong[strlen(currentSong)-1] = '\0';
//		} else {
//			currentSong = new char[strlen(song)+1];
//			strcpy(currentSong,song);
//		}}
//	const char* getCurrentSong() const
//	{ return currentSong; }
private:
	IGameLogic* logic;
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
	u32 then; //last frame time stamp
	IGUIImage* widgets[GAME_MENU_LENGTH];
	ITexture* digits[10]; //ten digits, nothing special

	//ITexture* pauseMenu[GP_LENGTH];
	IGUIImage* pauseMenu[GP_LENGTH];
	IGUIImage* hitImage[HI_LENGTH];
	IGUIImage* detectImage;
	GameInfo gameInfo;
	IGUIImage* score[SCORE_WIDTH];
	IGUIImage* combo[COMBO_WIDTH];
	IGUIImage* xSign;
	GameEventReceiver eventListener;
	ISoundEngine *soundEngine;
	void _initMenu();
	/* update both score */
	void _updateScore(u32 score);
	/* update combo */
	void _updateCombo(u32 delta);
	u32 _showPauseMenu();
	void _hidePauseMenu();
	u32 lastHit;
	u32 lastScore;
	int comboLast;
	Song* currentSong;
};

#endif /* GAMEOBJECT_H_ */
