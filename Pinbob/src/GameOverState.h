/*
 * GameOverState.h
 *
 *  Created on: Aug 21, 2011
 *      Author: yejiabin
 */

#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

#include "IState.h"
#include "GameInfo.h"

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
	{ info = currentInfo; }
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
	void _showScore();
	GameInfo* currentInfo;
};

#endif /* GAMEOVERSTATE_H_ */
