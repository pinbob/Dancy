/***********************************************************************
 * Module:  MenuHandler.h
 * Author:  liwenhaosuper
 * Modified: 2011��07��21�� 21:04:05
 * Purpose: Declaration of the class MenuHandler
 * Comment: Used when the game first start and provides select options
 ***********************************************************************/

#if !defined(__pibbob_logic_MenuHandler_h)
#define __pibbob_logic_MenuHandler_h

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif
#include "IState.h"
#include "irrKlang.h"

using namespace irrklang;

class MenuHandler : public IEventReceiver, public IState
{
public:
	MenuHandler(IrrlichtDevice *pDevice, StateMachine *pStateMachine,
			u32 titleWidth, u32 titleHeight, char* titlePath,
			u32 imgAmt, u32 imgWidth, u32 imgHeight, char** imgPath);
	~MenuHandler();
	virtual bool OnEvent (const SEvent &event);
	virtual u32 update();
	virtual void deactivate(IState *pNext);
	virtual void activate(IState *pPrevious);
private:
     //sound engine for menu 
	ISoundEngine *m_pSndEngine;
	ISceneNode *m_pMenu;
	ITimer *m_pTimer;
	u32 m_iMenuItem,m_iLastTime;
	bool m_bMoving,m_bSelect;

	//mouse event related
	//a struct to record info on the mouse state
	struct SMouseState {
		core::position2di Position;
		bool LeftButtonUp;
		SMouseState() :
		LeftButtonUp(false) {
		}
	} MouseState;
	bool lastHitStayed;
public:
	const SMouseState & getMouseState(void) const {
		return MouseState;
	}
	bool getLastHitStatus() const {
		return lastHitStayed;
	}
	void setLastHitStatus(bool newStatus) {
		lastHitStayed = newStatus;
	}
private:
	char* titlePath;
	ITexture* title;
	core::rect<s32> titleSize;
	core::position2d<s32> titlePos;

	u32 imgAmt;
	char** imgPath;
	ITexture** images;
	core::rect<s32> imgSize;
	core::position2d<s32>* imgPos;

	//load image files 
	bool LoadImage();
};

#endif
