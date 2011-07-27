/***********************************************************************
 * Module:  StateMachine.h
 * Author:  liwenhaosuper
 * Modified: 2011��07��21�� 16:39:14
 * Purpose: Declaration of the class StateMachine
 ***********************************************************************/

#if !defined(__pibbob_logic_StateMachine_h)
#define __pibbob_logic_StateMachine_h


#include "irrlicht.h"
#include "irrKlang.h"
#include "IState.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace irrklang;

class MenuHandler;
class GameHandler;
class IState;
class GameObject;

class StateMachine
{
public:
	StateMachine();
	virtual ~StateMachine();
	/**
	  * Initialize all states
	  * @param pDevice the Irrlicht device to be used
	*/
    virtual void initStates(IrrlichtDevice *pDevice);
	/**
		* clear all states
	*/
    virtual void clearStates();
	/**
		* set the m_bGraphicsChanged flag to "true"
		* @see m_bGraphicsChanged
	*/
    void graphicsChanged();
	/**
		* change the m_bDrawScene flag
		* @see m_bDrawScene
	*/
	void setDrawScene(bool b);
	/**
		* retrieve the sound engine
		* @return the sound engine
	*/
	ISoundEngine *getSoundEngine();
	 /**
		* start and run the state machine
		* @return unimportant
	*/
    u32 run();

	/**
		* get the aspect ratio
		* @return the aspect ratio
	*/
    f32 getAspectRatio();

	/**
		* get the "preview" scene manager
		* @return the preview scene manager
	*/
    ISceneManager *getPreviewSceneManager();

    /**
     * get the framerate
     * @return the framerate
     */
    u32 getFps();

public:
	array<IState*> m_aStates;						/**< a list of all states */
	IState *m_pActive;										/**< the active state */
	IrrlichtDevice  *m_pDevice;
	IVideoDriver    *m_pDriver;
	ISceneManager   *m_pSmgr;							/**< the main scene manager */
	ISceneManager   *m_pPreviewManager;		/**< the scene manager for level preview */
	IGUIEnvironment *m_pGuienv;
	IGUIFont        *m_pFont;							/**< the new standard font */
	bool m_bGraphicsChanged;			/**< this flag must be "true" if the graphics mode needs re-initialization, e.g. to chane it */
	bool m_bDrawScene;						/**< should the state machine draw the scene, or will the active state take care of that? */
	//ISoundEngine *m_pSndEngine;		/**< the sound engine */
	u32 m_iFps;

	void addState(IState *pState);
	/************************************************************************/
	/*  system element                                                                    */
	/************************************************************************/
	MenuHandler           **m_pMenu;					/** all menu state */         
	GameObject            *m_pGameObj;              /**< the "game" state */
	//add more elements here

};

#endif
