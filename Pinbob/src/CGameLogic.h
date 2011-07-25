/***********************************************************************
 * Module:  CGameLogic.h
 * Author:  Administrator
 * Modified: 2011��07��21�� 21:54:04
 * Purpose: Declaration of the class CGameLogic
 ***********************************************************************/

#if !defined(__Game_CGameLogic_h)
#define __Game_CGameLogic_h

#include "IGameLogic.h"



class CGameLogic : public IGameLogic
{
public:
	CGameLogic();
	virtual ~CGameLogic();
	virtual void setDevice(IrrlichtDevice *pDevice);
	virtual void setGame(GameObject *pGame);
/*
	virtual void update() 
	{
		throw std::exception("The method or operation is not implemented.");
	}

	virtual void init() 
	{
		throw std::exception("The method or operation is not implemented.");
	}

	virtual void setGameState( u32 iState ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

	virtual void setTimer( ITimer *pTimer ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

	virtual u32 getGameState() 
	{
		throw std::exception("The method or operation is not implemented.");
	}
*/
protected:
private:

};

#endif
