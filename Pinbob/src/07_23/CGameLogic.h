/***********************************************************************
 * Module:  CGameLogic.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:54:04
 * Purpose: Declaration of the class CGameLogic
 ***********************************************************************/

#if !defined(__Game_CGameLogic_h)
#define __Game_CGameLogic_h

#include "IGameLogic.h"
#include "GameObject.h"



class CGameLogic : public IGameLogic
{
public:
	CGameLogic();
	virtual ~CGameLogic();
	virtual void setDevice(IrrlichtDevice *pDevice);
	virtual void setGame(GameObject *pGame);

	virtual void update() ;

	virtual void init() ;

	virtual void setGameState( u32 iState ) ;

	virtual void setTimer( ITimer *pTimer ) ;

	virtual u32 getGameState() ;

protected:
private:
	eGameLogicState m_iState;  //current state of the game
	ITimer *m_pTimer;
	IrrlichtDevice *m_pDevice;
	GameObject *m_pGame;  //the game object that it belongs to
	u32 m_iCountDown;    //number of count downs
	u32 m_iTime; //timer state record
	u32 m_iStartTime; // the time when player begin to dance

};

#endif