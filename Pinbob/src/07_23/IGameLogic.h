/***********************************************************************
 * Module:  IGameLogic.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 22:21:51
 * Purpose: Declaration of the class IGameLogic
 * Comment: This is an interface that needs to be implemented to get game logic working. 
 *The idea behind this is to implement  it once for the "normal" playing (like "single player" or "splitscreen")
 * and make another implementation for network gaming or multiplayer gaming
 ***********************************************************************/

#if !defined(__Game_IGameLogic_h)
#define __Game_IGameLogic_h

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//the game logic state enum 
enum eGameLogicState {
	eGameStateInitGame=0,//initialize the game element.
	eGameStateReady1,   //the game element has finished drawing
	eGameStateReady2,    //players are ready
	eGameStateCountdown1, //initialize the count down and begin to count, then transfer to countdown2
	eGameStateCountdown2, //when the count down is not finished, transfers to countdown1 to continue count down, else transfers to state go
	eGameStateGo,       //"go" state
	eGameStatePlay,     //begin to play
	eGameStateStarting,  //playing the game
	eGameStateFinished, //game finished 
	eGameStateGameOver1, //game over and start showing the game score and other info
	eGameStateGameOver2,  //show other info such as options
};

//predeclared class
class GameObject;

class IGameLogic
{
public:
	virtual ~IGameLogic() { }
	virtual void setDevice(IrrlichtDevice *pDevice)=0;
	/**
		* Set the game object. The game object is responsible for displaying GUI stuff of the main game scene. 
		* GUI elements of the players
		* are displayed somewhere else.
		* @param pGame the Game object
	*/
    virtual void setGame(GameObject *pGame)=0;
	/**
		* Set the timer
		* @param pTimer the timer
		*/
    virtual void setTimer(ITimer *pTimer)=0;

	/**
		* Init the game logic
	*/
    virtual void init()=0;

	/**
	    * get the current game state
		* @return the current game state
	*/
    virtual u32 getGameState()=0;

	/**
		* set a new game state
		* @param iState the new game state
	*/
    virtual void setGameState(u32 iState)=0;

	/**
		* This method need to be called once per frame
	 */
    virtual void update()=0;



protected:
private:

};

#endif