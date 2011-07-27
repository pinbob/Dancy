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

struct GameMenuConfig {
	core::position2d<s32> position;
	core::rect<s32> size;
	const char* filename;
};

const GameMenuConfig GAME_MENU_CONFIG[GAME_MENU_LENGTH] = {
		{position2d<s32>(225, 410),rect<s32>(0, 0, 190, 70),"asset/images/menu.png"},
		{position2d<s32>(0, 130),rect<s32>(0, 0, 130, 110),"asset/images/ulArea.png"},
		{position2d<s32>(0, 240),rect<s32>(0, 0, 130, 110),"asset/images/dlArea.png"},
		{position2d<s32>(510, 130),rect<s32>(0, 0, 130, 110),"asset/images/urArea.png"},
		{position2d<s32>(510, 240),rect<s32>(0, 0, 130, 110),"asset/images/drArea.png"}
};

enum PauseMenu {
	GP_CONTINUE,
	GP_MAIN_MENU,
	GP_RESTART,
	GP_MENU_HEAD,
	GP_LENGTH
};

struct ResourceLayout {
	const char* filename;
	vector2d<s32> position;
};

enum IN_GAME_SUBSTATE {
	IG_UPDATE,
	IG_PAUSE
};

const ResourceLayout GP_LAYOUT[GP_LENGTH] = {
	{"asset/images/GP_continue.png",vector2d<s32>(200,200)},
	{"asset/images/GP_mainMenu.png",vector2d<s32>(200,250)},
	{"asset/images/GP_restart.png",vector2d<s32>(200,300)},
	{"asset/images/GP.png",vector2d<s32>(200,120)}
};

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
private:
	IGameLogic* logic;
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
	u32 then; //last frame time stamp
	ITexture** widgets;
	ITexture* digits[10]; //ten digits, nothing special
	//ITexture* pauseMenu[GP_LENGTH];
	IGUIImage* pauseMenu[GP_LENGTH];
	GameInfo gameInfo;
	IGUIImage* score[SCORE_WIDTH];
	GameEventReceiver eventListener;
	void _initMenu();
	void _updateScore(u32 score);
	void _showPauseMenu();
	void _hidePauseMenu();
	u32 lastHit;
	u32 lastScore;
};

#endif /* GAMEOBJECT_H_ */