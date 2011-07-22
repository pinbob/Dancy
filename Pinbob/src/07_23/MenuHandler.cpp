/***********************************************************************
 * Module:  MenuHandler.cpp
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:04:05
 * Purpose: Declaration of the class MenuHandler
 * Comment: Used when the game first start and provides select options
 ***********************************************************************/

#include "MenuHandler.h"
#include "StateMachine.h"


MenuHandler::MenuHandler(IrrlichtDevice *pDevice, StateMachine *pStateMachine) : IState(pDevice,pStateMachine) {
	m_iMenuItem=-1;
	lastHitStayed = false;
	//image position
	imgPos[0] = position2d<s32>(300, 0);
	imgPos[1] = position2d<s32>(300, 100);
	imgPos[2] = position2d<s32>(300, 200);
	imgPos[3] = position2d<s32>(300, 300);
	imgPos[4] = position2d<s32>(300, 400);
	imgPos[5] = position2d<s32>(300, 500);
	//imageSize
	imgSize[0] = rect<s32>(0, 0, 250, 80);
	imgSize[1] = rect<s32>(0, 0, 250, 50);
	imgSize[2] = rect<s32>(0, 0, 250, 50);
	imgSize[3] = rect<s32>(0, 0, 250, 50);
	imgSize[4] = rect<s32>(0, 0, 250, 50);
	imgSize[5] = rect<s32>(0, 0, 250, 50);
	LoadImage();
	pDevice->setEventReceiver(this);
}

void MenuHandler::activate(IState *pPrevious) {
	m_pTimer=m_pDevice->getTimer();
	while (m_pTimer->isStopped()) m_pTimer->start();
	m_iLastTime=m_pTimer->getTime();
	//in this IState instance, I choose to draw the scene myself
	m_pStateMachine->setDrawScene(false);
	//draw the scene
	m_pDriver->beginScene(true,true,SColor(0,200,200,200));
	for(int i=0;i<6;i++)
	    m_pDriver->draw2DImage(images[i], imgPos[i], imgSize[i], 0,
		    video::SColor(255, 255, 255, 255), true);
	m_pSmgr->drawAll();
	m_pGuienv->drawAll();
	m_pDriver->endScene();
	
}

void MenuHandler::deactivate(IState *pNext) {
	m_pDevice->getSceneManager()->clear();
	m_pDevice->getCursorControl()->setVisible(true);
	m_pGuienv->clear();
}

bool MenuHandler::LoadImage()
{
	images = new ITexture*[6];
	images[0] = m_pDriver->getTexture("asset/images/menu/dancy.png");
	images[1] = m_pDriver->getTexture("asset/images/menu/startGame1.png");
	images[2] = m_pDriver->getTexture("asset/images/menu/options1.png");
	images[3] = m_pDriver->getTexture("asset/images/menu/highScores1.png");
	images[4] = m_pDriver->getTexture("asset/images/menu/credits1.png");
	images[5] = m_pDriver->getTexture("asset/images/menu/quit1.png");
	return true;

}

u32 MenuHandler::update() {
	u32 iDiff,iThisTime;

	iThisTime=m_pTimer->getTime();
	iDiff=iThisTime-m_iLastTime;
	m_iLastTime=iThisTime;

	int mouseX = MouseState.Position.X;
	int mouseY = MouseState.Position.Y;
	if (MouseState.LeftButtonDown ) {
		m_bSelect=false;
		if(mouseX<=500&&mouseX>=300)
		{
			if(mouseY>=100&&mouseY<=150)
			{
				//start game
				m_iMenuItem = 0;
				m_bSelect=true;
				printf("start game!");

			}
			else if(mouseY>=200&&mouseY<=250)
			{
				//options
				m_iMenuItem = 1;
				m_bSelect=true;
				printf("options!");
			}
			else if(mouseY>=300&&mouseY<=350)
			{
				//high scores
				m_iMenuItem = 2;
				m_bSelect=true;
				printf("high scores!");
			}
			else if(mouseY>=400&&mouseY<=450)
			{
				//credits
				m_iMenuItem = 3;
				m_bSelect=true;
				printf("credits!");
			}
			else if(mouseY>=500&&mouseY<=550)
			{
				//quit
				m_iMenuItem = 4;
				m_bSelect=true;
				printf("quit!");
			}
			else {
				m_bSelect=false;
				printf("liwenhaosuper!");
			}
		}
	}
	if (m_bSelect) {
		switch (m_iMenuItem) {
	    // complete it later on...
	    // be aware that the return value are corresponding to the IState index that you want to switch to
		case 0: return  1; break; //start game
		case 1: return  2; break; //options
		case 2: return  3; break; //high scores
		case 3: return  4; break; //credits
		case 4: return  5; break; //quit
		}
	}
	return 0;
}

bool MenuHandler::OnEvent(const SEvent &event) {
	// Remember the mouse state
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_PRESSED_DOWN:
			MouseState.LeftButtonDown = true;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			MouseState.LeftButtonDown = false;
			break;
		case EMIE_MOUSE_MOVED:
			MouseState.Position.X = event.MouseInput.X;
			MouseState.Position.Y = event.MouseInput.Y;
			break;
		default:
			break;
		}
	}
	return false;
}
