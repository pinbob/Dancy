/***********************************************************************
 * Module:  IState.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 16:39:14
 * Purpose: Declaration of the class IState
 ***********************************************************************/

#if !defined(__pibbob_logic_IState_h)
#define __pibbob_logic_IState_h

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif
#include "StateMachine.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//predeclared class
class StateMachine;

class IState
{
public:
   IState(IrrlichtDevice* pDevice, StateMachine* pStateMachine)
   {
	   m_pDevice=pDevice;
	   m_pDriver=m_pDevice->getVideoDriver();
	   m_pSmgr  =m_pDevice->getSceneManager();
	   m_pGuienv=m_pDevice->getGUIEnvironment();
	   m_pStateMachine=pStateMachine;
   }
   enum StateType{
	   MAIN_MENU_STATE = 1,   //main menu
	   MODE_STATE,        //mode menu
	   SONG_STATE,        //song state  
	   CREDITS_STATE,     //credits
	   START_GAME,        //start game
	   SCORE_STATE,        //high score 
	   OPTIONS_STATE,     //options
	   QUIT_STATE = 10086       //quit game
   };

   virtual ~IState(){}
   /* This method is called by the state machine on state activation. Must be implemented in subclass
    * @param pPrevious the previously active state */
   virtual void activate(IState* pPrevious)=0;
   /* This method is called by the state machine on state deactivation. Must be implemented in subclass
    * @param pNext the next active state */
   virtual void deactivate(IState* pNext)=0;
   /*  This method is called by the state manager on each form.
    *  @return "0" is no state change is wanted, "index of new state-1" to switch to another state, out of bounds index to quit program */
   virtual u32 update(void)=0;
   virtual void setNum(u32 iNum){ m_iNum = iNum;}
   virtual u32 getNum(void){ return m_iNum;}
protected:
	/**< the Irrlicht device */
   IrrlichtDevice* m_pDevice;
   /**< the Irrlicht video driver */
   IVideoDriver* m_pDriver;
   /**< the Irrlicht scene manager */
   ISceneManager* m_pSmgr;
   /**< the Irrlicht GUI environment */
   IGUIEnvironment* m_pGuienv;
   /**< the index of this state */
   u32 m_iNum;
   /**< the state machine this state belongs to */
   StateMachine* m_pStateMachine;
};

#endif