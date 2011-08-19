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
			char* backPath, u32 titleWidth, u32 titleHeight, char* titlePath,
			u32 imgAmt, u32 imgWidth, u32 imgHeight, char** imgPath, u32 focusIndex);
	virtual ~MenuHandler();
	virtual bool OnEvent (const SEvent &event);
	virtual u32 update();
	virtual void deactivate(IState *pNext);
	virtual void activate(IState *pPrevious);

private:
	ISoundEngine *m_pSndEngine;//sound engine for menu
	//ISceneNode *m_pMenu;
	ITimer *m_pTimer;
	u32 m_focusItem;//shows which menu is focused
	static StateType m_lastfocusItem; //remember last focus item
	u32 m_iLastTime;
	bool m_bMoving,m_bSelect;
	IState *m_pPrevious;

	//mouse event related
	//a struct to record info on the mouse state
	struct SMouseState {
		core::position2di mouseDownPos;
		core::position2di mouseCurPos;
		bool isMouseUp;
		SMouseState() :  mouseDownPos(0, 0), mouseCurPos(0, 0), isMouseUp(false){}
	} MouseState;

public:
	const SMouseState & getMouseState(void) const {
		return MouseState;
	}

private:
    char* backPath;//background path
    ITexture* back;
        
	char* titlePath;
	ITexture* title;
	core::rect<s32> titleSize;
	core::position2d<s32> titlePos;

	u32 imgAmt;
	char** imgPath;
	ITexture** images;
	core::rect<s32> imgSize;
	core::position2d<s32>* imgPos;

    void drawScene();
	//load image files 
	bool LoadImage(u32 focusIndex);
        //draw menu items
    void drawMenu();
};

#endif
