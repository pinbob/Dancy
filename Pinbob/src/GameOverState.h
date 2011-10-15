/*
 * GameOverState.h
 *
 *  Created on: Aug 21, 2011
 *      Author: yejiabin
 */

#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

#include "IState.h"
#include "Config.h"
#include "StateMachine.h"
#include "GameInfo.h"

static const char* goverImage[5] = {
		"asset/images/perfect.png",
		"asset/images/wellDone.png",
		"asset/images/good.png",
		"asset/images/bad.png",
		"asset/images/missed.png"
};

class GameOverState: public IState, public IEventReceiver {
public:
	GameOverState(IrrlichtDevice *pDevice,
			StateMachine *pStateMachine);
	virtual ~GameOverState();
	virtual u32 update(void);
	virtual void activate(IState* pPrevious);
	virtual void deactivate(IState* pNext);
	virtual bool OnEvent(const SEvent& event);
	void setGameInfo(GameInfo* info)
	{ currentInfo = info; }
private:
	struct SMouseState {
		bool isMouseUp;
		core::position2di mouseDownPos;
		core::position2di mouseCurPos;
		SMouseState() :
				isMouseUp(false), mouseDownPos(0, 0), mouseCurPos(0, 0) {
		}
	} MouseState;
	IGUIImage* back;
	ITexture* digit[10];
	void _init();
	void _showScore(int idx,u32 score);
	GameInfo* currentInfo;
	u32 ret; // return value


	u32 swidth, sheight;
};

#endif /* GAMEOVERSTATE_H_ */
