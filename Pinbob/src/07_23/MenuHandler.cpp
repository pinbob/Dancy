/***********************************************************************
 * Module:  MenuHandler.cpp
 * Author:  liwenhaosuper
 * Modified: 2011��07��21�� 21:04:05
 * Purpose: Declaration of the class MenuHandler
 * Comment: Used when the game first start and provides select options
 ***********************************************************************/

#include "MenuHandler.h"
#include "StateMachine.h"
#include <iostream>
using namespace std;

MenuHandler::MenuHandler(IrrlichtDevice *pDevice, StateMachine *pStateMachine,
		u32 titleWidth, u32 titleHeight, char* titlePath,
		u32 imgAmt, u32 imgWidth, u32 imgHeight, char** imgPath) :
		IState(pDevice,pStateMachine){
	m_iMenuItem=-1;
	lastHitStayed = false;

	this->imgAmt = imgAmt;
	this->imgSize = rect<s32>(0, 0, imgWidth, imgHeight);
	this->titleSize = rect<s32>(0, 0, titleWidth, titleHeight);

	//image path
	this->imgPath = new char*[imgAmt];
	for (u32 i = 0; i < imgAmt; ++i){
		this->imgPath[i] = imgPath[i];
		cout<<"imagePath["<<i<<"] = "<<this->imgPath[i]<<endl;
	}
	this->titlePath = titlePath;

	//image position
	u32 screenWidth = m_pDevice->getVideoDriver()->getScreenSize().Width;
	u32 screenHeight = m_pDevice->getVideoDriver()->getScreenSize().Height;
	cout<<"width: "<<screenWidth<<", height: "<<screenHeight<<endl;
	this->titlePos = position2d<s32>(
			(screenWidth - titleWidth) / 2,
			(screenHeight - titleHeight - imgHeight * imgAmt) / 2);
	for (u32 i = 0; i < imgAmt; ++i){
		this->imgPos[i] = position2d<s32>(
				(screenWidth - imgWidth) / 2,
				(screenHeight - titleHeight - imgHeight * imgAmt) / 2 + titleHeight + imgHeight * i);
	}

	LoadImage();
	pDevice->setEventReceiver(this);
	cout<<"end of init\n";
}

MenuHandler::~MenuHandler(){
	delete []imgPath;
	delete []images;
}

void MenuHandler::activate(IState *pPrevious) {
	m_pTimer=m_pDevice->getTimer();
	while (m_pTimer->isStopped()) m_pTimer->start();
	m_iLastTime=m_pTimer->getTime();
	//in this IState instance, I choose to draw the scene myself
	m_pStateMachine->setDrawScene(false);
	//draw the scene
	m_pDriver->beginScene(true,true,SColor(0,200,200,200));
cout<<"he\n";
	m_pDriver->draw2DImage(title, titlePos, titleSize, 0,
			    video::SColor(255, 255, 255, 255), true);
	cout<<"draw\n";
	/*
	for(u32 i=0;i<imgAmt;i++){
		cout<<i;
	    m_pDriver->draw2DImage(images[i], imgPos[i], imgSize, 0,
		    video::SColor(255, 255, 255, 255), true);
	}*/
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
	images = new ITexture*[imgAmt];
	for (u32 i = 0; i < imgAmt; ++i){
		cout<<"load:"<<i<<endl;
		images[i] = m_pDriver->getTexture(imgPath[i]);
	}
	title = m_pDriver->getTexture(titlePath);
	return true;
}

u32 MenuHandler::update() {
	u32 iDiff,iThisTime;

	iThisTime=m_pTimer->getTime();
	iDiff=iThisTime-m_iLastTime;
	m_iLastTime=iThisTime;

	int mouseX = MouseState.Position.X;
	int mouseY = MouseState.Position.Y;
	if (MouseState.LeftButtonUp ) {
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
			MouseState.LeftButtonUp= false;
			break;
 		case EMIE_LMOUSE_LEFT_UP:
 			MouseState.LeftButtonUp = true;
 			break;
		case EMIE_MOUSE_MOVED:
			MouseState.Position.X = event.MouseInput.X;
			MouseState.Position.Y = event.MouseInput.Y;
			break;
		default:
			MouseState.LeftButtonUp = false;
			break;
		}
	}
	return false;
}
