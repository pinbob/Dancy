/***********************************************************************
 * Module:  MenuHandler.cpp
 * Author:  liwenhaosuper
 * Modified: 2011��07��21�� 21:04:05
 * Purpose: Declaration of the class MenuHandler
 * Comment: Used when the game first start and provides select options
 ***********************************************************************/

#include "MenuHandler.h"
#include "StateMachine.h"
#include <string>
#include <iostream>
using namespace std;

MenuHandler::MenuHandler(IrrlichtDevice *pDevice, StateMachine *pStateMachine,
		u32 titleWidth, u32 titleHeight, char* titlePath,
		u32 imgAmt, u32 imgWidth, u32 imgHeight, char** imgPath, u32 focusIndex) :
		IState(pDevice,pStateMachine), m_focusItem(focusIndex){

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
	this->imgPos = new core::position2d<s32>[imgAmt];
	this->titlePos = position2d<s32>(
			(screenWidth - titleWidth) / 2,
			(screenHeight - titleHeight - imgHeight * imgAmt) / 2);
	for (u32 i = 0; i < imgAmt; ++i){
		this->imgPos[i] = position2d<s32>(
				(screenWidth - imgWidth) / 2,
				(screenHeight - titleHeight - imgHeight * imgAmt) / 2 + titleHeight + imgHeight * i);
	}

	LoadImage(m_focusItem);
	pDevice->setEventReceiver(this);
}

MenuHandler::~MenuHandler(){
	delete []imgPath;
	delete []images;
	delete []imgPos;
}

void MenuHandler::activate(IState *pPrevious) {
	m_pPrevious = pPrevious;
	m_pTimer=m_pDevice->getTimer();
	while (m_pTimer->isStopped()) m_pTimer->start();
	m_iLastTime=m_pTimer->getTime();
	//in this IState instance, I choose to draw the scene myself
	m_pStateMachine->setDrawScene(false);
	//draw the scene
	m_pDriver->beginScene(true,true,SColor(0,200,200,200));
	m_pDriver->draw2DImage(title, titlePos, titleSize, 0,
			    video::SColor(255, 255, 255, 255), true);

	for(u32 i=0;i<imgAmt;i++){
		core::position2d<s32> newImgPos;
		newImgPos.X = imgPos[i].X;
		newImgPos.Y = imgPos[i].Y + MouseState.mouseCurPos.Y - MouseState.mouseDownPos.Y;
		if (newImgPos.Y + imgSize.getHeight() < imgPos[0].Y){//upper than img border
			newImgPos.Y += imgSize.getHeight() * imgAmt;
		    m_pDriver->draw2DImage(images[i], newImgPos, imgSize, 0,
			    video::SColor(255, 255, 255, 255), true);

		}else if (newImgPos.Y < imgPos[0].Y){//upper half clip
			core::rect<s32>* clipRect = new core::rect<s32>(0, imgPos[0].Y - newImgPos.Y,
										imgSize.getWidth(), imgSize.getHeight());
		    m_pDriver->draw2DImage(images[i], newImgPos, imgSize, clipRect,
			    video::SColor(255, 255, 255, 255), true);

		    //another half that is at bottom
		    newImgPos.Y += imgSize.getHeight() * imgAmt;
		    clipRect = new core::rect<s32>(0, 0,
		    		imgSize.getWidth(), imgPos[0].Y + imgSize.getHeight() * imgAmt - newImgPos.Y);
			m_pDriver->draw2DImage(images[i], newImgPos, imgSize, clipRect,
					video::SColor(255, 255, 255, 255), true);
			delete clipRect;

		}else if (newImgPos.Y > imgPos[0].Y + imgSize.getHeight() * imgAmt){//lower than img border
			newImgPos.Y -= imgSize.getHeight() * imgAmt;
			m_pDriver->draw2DImage(images[i], newImgPos, imgSize, 0,
						    video::SColor(255, 255, 255, 255), true);

		}else if (newImgPos.Y + imgSize.getHeight() > imgPos[0].Y + imgSize.getHeight() * imgAmt){
			core::rect<s32>* clipRect = new core::rect<s32>(0, 0,
					imgSize.getWidth(), imgPos[0].Y + imgSize.getHeight() * imgAmt - newImgPos.Y);
			m_pDriver->draw2DImage(images[i], newImgPos, imgSize, clipRect,
				video::SColor(255, 255, 255, 255), true);

			//another half that is at top
			newImgPos.Y -= imgSize.getHeight() * imgAmt;
			clipRect = new core::rect<s32>(0, imgPos[0].Y - newImgPos.Y,
					imgSize.getWidth(), imgSize.getHeight());
			m_pDriver->draw2DImage(images[i], newImgPos, imgSize, clipRect,
					video::SColor(255, 255, 255, 255), true);
			delete clipRect;

		}else{
		    m_pDriver->draw2DImage(images[i], newImgPos, imgSize, 0,
			    video::SColor(255, 255, 255, 255), true);
		}

	}
	m_pSmgr->drawAll();
	m_pGuienv->drawAll();
	m_pDriver->endScene();
	
}

void MenuHandler::deactivate(IState *pNext) {
	m_pDevice->getSceneManager()->clear();
	m_pDevice->getCursorControl()->setVisible(true);
	m_pGuienv->clear();
}

bool MenuHandler::LoadImage(u32 focusIndex)
{
	images = new ITexture*[imgAmt];
	for (u32 i = 0; i < imgAmt; ++i){
		//append 1.png or 0.png to imgPath
		char* path = new char[strlen(imgPath[i]) + 5];//extra space for `1.png'
		strcpy(path, imgPath[i]);
		if (i == focusIndex){
			strcat(path, "1.png");
		}else{
			strcat(path, "0.png");
		}
		images[i] = m_pDriver->getTexture(path);
		delete path;
	}
	title = m_pDriver->getTexture(titlePath);
	return true;
}

u32 MenuHandler::update() {
	u32 iDiff,iThisTime;

	iThisTime=m_pTimer->getTime();
	iDiff=iThisTime-m_iLastTime;
	m_iLastTime=iThisTime;

	return 0;
}

bool MenuHandler::OnEvent(const SEvent &event) {
	// Remember the mouse state
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		MouseState.mouseDownPos.X = event.MouseInput.X;
		MouseState.mouseDownPos.Y = event.MouseInput.Y;
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_PRESSED_DOWN:
			//when mouse down, set isMouseDown to be true
			MouseState.isMouseDown = true;
			MouseState.mouseCurPos.X = event.MouseInput.X;
			MouseState.mouseCurPos.Y = event.MouseInput.Y;
			break;
 		case EMIE_LMOUSE_LEFT_UP:
 			//when mouse up, set isMouseDown to be false
			MouseState.isMouseDown = false;
 			break;
		case EMIE_MOUSE_MOVED:
			//when mouse move, if is mouseDown, remember where
			if (MouseState.isMouseDown){
					m_bSelect=false;
					for (u32 i = 0; i < imgAmt; ++i){
						//if mouse pos is within imgPos
						if (event.MouseInput.X > imgPos[i].X &&
							event.MouseInput.X < imgPos[i].X + imgSize.getWidth() &&
							event.MouseInput.Y > imgPos[i].Y &&
							event.MouseInput.Y < imgPos[i].Y + imgSize.getHeight()){
								//if is not the same as before, reactivate it
								if (m_focusItem != i){
									m_focusItem = i;
									LoadImage(i);
									activate(m_pPrevious);
									cout<<"Clicked: "<<i<<endl;
								}
								break;
						}
					}
			}
			break;
		default:
			break;
		}
	}
	return false;
}
