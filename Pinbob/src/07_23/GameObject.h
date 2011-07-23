/***********************************************************************
 * Module:  GameObject.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 23:49:42
 * Purpose: Declaration of the class GameObject
 * Comment: This class handles all player-specific stuff. It controls the AR, the camera and the player specific GUI elements
 ***********************************************************************/

#if !defined(__Game_GameObject_h)
#define __Game_GameObject_h

#include "irrlicht.h"
#include "irrklang.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#pragma comment(lib,"irrklang.lib")
#endif
#include "IState.h"
#include "StateMachine.h"
#include "IGameLogic.h"
#include "Score.h"
#include "Arrow.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;

class IARManager;

class GameObject:public IState,public IEventReceiver
{
public:
	GameObject(IrrlichtDevice *pDevice, StateMachine *pStateMachine);
	virtual ~GameObject();

   virtual u32 update( void ) ;

   virtual void activate( IState* pPrevious ) ;

   virtual void deactivate( IState* pNext ) ;

   virtual bool OnEvent( const SEvent& event ) ;
   //initialize all the necessary game element
   void InitGameObject();
   //get the sound engine of the game
   ISoundEngine *getSoundEngine();
   //setter and getter method of game logic 
   IGameLogic * SetGameLogic() const { return m_pLogic; }
   void GetGameLogic(IGameLogic * val) { m_pLogic = val; }

protected:
private:
	ISoundEngine *m_pSndEngine; // the sound engine used to handle the sound
	IARManager* iARManager;
	Score* score;
	Arrow* arrow;
	ITimer *m_pTimer;
	//game logic of the gameobject
	IGameLogic *m_pLogic;
	IGUIImage *m_pCountdown,//responsible for the count down image
		*m_pGameOver; //responsible for the game over image
	array<ITexture *> m_aCountdown;
	bool m_bQuitGame; //whether should quit the game or not
	u32 m_iNextState, //the next game state
	    m_iState;    //the current game state
	
	//TODO:add more elements here. 
	//Maybe we should add a progress bar for the GUI thread while a working thread is initializing.

};

#endif