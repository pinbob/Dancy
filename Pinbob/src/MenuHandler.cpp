/***********************************************************************
 * Module:  MenuHandler.cpp
 * Author:  liwenhaosuper
 * Modified: 2011��07��21�� 21:04:05
 * Purpose: Declaration of the class MenuHandler
 * Comment: Used when the game first start and provides select options
 ***********************************************************************/

#include "MenuHandler.h"
#include "StateMachine.h"
#include "IState.h"
#include <string>
#include <iostream>
using namespace std;

MenuHandler::StateType MenuHandler::m_lastfocusItem = MAIN_MENU_STATE;

MenuHandler::MenuHandler(IrrlichtDevice *pDevice, StateMachine *pStateMachine,
        char* backPath, u32 titleWidth, u32 titleHeight, char* titlePath,
        u32 imgAmt, u32 imgWidth, u32 imgHeight, char** imgPath, u32 focusIndex) :
IState(pDevice, pStateMachine), m_focusItem(focusIndex) {

    this->imgAmt = imgAmt;
    this->imgSize = rect<s32 > (0, 0, imgWidth, imgHeight);
    this->titleSize = rect<s32 > (0, 0, titleWidth, titleHeight);

    //image path
    this->imgPath = new char*[imgAmt];
    for (u32 i = 0; i < imgAmt; ++i) {
        this->imgPath[i] = imgPath[i];
        cout << "imagePath[" << i << "] = " << this->imgPath[i] << endl;
    }
    this->backPath = backPath;
    this->titlePath = titlePath;

    //image position
    u32 screenWidth = m_pDevice->getVideoDriver()->getScreenSize().Width;
    u32 screenHeight = m_pDevice->getVideoDriver()->getScreenSize().Height;
    this->imgPos = new core::position2d<s32>[imgAmt];
    this->titlePos = position2d<s32 > (
            (screenWidth - titleWidth) / 2,
            (screenHeight - titleHeight - imgHeight * imgAmt) / 2);
    for (u32 i = 0; i < imgAmt; ++i) {
        this->imgPos[i] = position2d<s32 > (
                (screenWidth - imgWidth) / 2,
                (screenHeight - titleHeight - imgHeight * imgAmt) / 2 + titleHeight + imgHeight * i);
    }

    LoadImage(m_focusItem);
    pDevice->setEventReceiver(this);
	//m_bSelect = false;
	m_focusItem = 0;
}

MenuHandler::~MenuHandler() {
    delete []imgPath;
    delete []images;
    delete []imgPos;
}

void MenuHandler::activate(IState *pPrevious) {
	m_pDevice->setEventReceiver(this);
	MouseState.isMouseUp = false;
    m_pPrevious = pPrevious;
    m_pTimer = m_pDevice->getTimer();
    while (m_pTimer->isStopped()) m_pTimer->start();
    m_iLastTime = m_pTimer->getTime();
    //in this IState instance, I choose to draw the scene myself
    m_pStateMachine->setDrawScene(false);
    drawScene();
}

void MenuHandler::drawScene(){
    //draw the scene
    m_pDriver->beginScene(true, true, SColor(0, 200, 200, 200));
    
    m_pDriver->draw2DImage(back, core::position2d<s32>(0, 0), 
            core::rect<s32>(0, 0, m_pDevice->getVideoDriver()->getScreenSize().Width, 
            m_pDevice->getVideoDriver()->getScreenSize().Height), 0,
            video::SColor(255, 255, 255, 255), true);
    m_pDriver->draw2DImage(title, titlePos, titleSize, 0,
            video::SColor(255, 255, 255, 255), true);

    drawMenu();

    m_pSmgr->drawAll();
    m_pGuienv->drawAll();
    m_pDriver->endScene();
}

void MenuHandler::drawMenu() {
    for (u32 i = 0; i < imgAmt; i++) {
        m_pDriver->draw2DImage(images[i], imgPos[i], imgSize, 0,
                video::SColor(255, 255, 255, 255), true);
    }
}

void MenuHandler::deactivate(IState *pNext) {
    m_pDevice->getSceneManager()->clear();
    m_pDevice->getCursorControl()->setVisible(true);
    m_pGuienv->clear();
}

bool MenuHandler::LoadImage(u32 focusIndex) {
    images = new ITexture*[imgAmt];
    for (u32 i = 0; i < imgAmt; ++i) {
        //append 1.png or 0.png to imgPath
        char* path = new char[strlen(imgPath[i]) + 6]; //extra space for `1.png'
        strcpy(path, imgPath[i]);
        if (i == focusIndex) {
            strcat(path, "1.png");
        } else {
            strcat(path, "0.png");
        }
        images[i] = m_pDriver->getTexture(path);
        delete path;
    }
    back = m_pDriver->getTexture(backPath);
    title = m_pDriver->getTexture(titlePath);
    return true;
}

u32 MenuHandler::update() {
    u32 iDiff, iThisTime;

    iThisTime = m_pTimer->getTime();
    iDiff = iThisTime - m_iLastTime;
    m_iLastTime = iThisTime;
	if(m_bSelect==true&& MouseState.isMouseUp==true)
	{
		MouseState.isMouseUp = false;
		m_bSelect = false;
		switch(m_focusItem)
		{
		case 0: 
			if(m_lastfocusItem==MAIN_MENU_STATE)  // we are now in main menu
			{
				printf("start game option clicked!\n");
				m_lastfocusItem = MODE_STATE;
				return MODE_STATE;
			}
			else if(m_lastfocusItem ==MODE_STATE) //we are now in mode menu
			{
				printf("song state clicked!\n");
				m_lastfocusItem = SONG_STATE;
				return SONG_STATE;
			}
			else if(m_lastfocusItem == SONG_STATE) //we are now in song state
			{
				printf("start game now!\n");
				m_lastfocusItem = START_GAME;
				return START_GAME;
			}
			break; 
		case 1:  
			if(m_lastfocusItem == MAIN_MENU_STATE)//we are now in main menu
			{
				printf("options selected\n");
				m_lastfocusItem = OPTIONS_STATE;
				return OPTIONS_STATE;
			}
			else if(m_lastfocusItem ==MODE_STATE)//we are now in mode menu
			{
				printf("back!\n");
				m_lastfocusItem = MAIN_MENU_STATE;
				return MAIN_MENU_STATE;
			}
			break;     
		case 2:  
		   if(m_lastfocusItem == MAIN_MENU_STATE) //now in main menu
		   {
			   printf("high score selected\n");
			   m_lastfocusItem = SCORE_STATE;
			   return SCORE_STATE;
		   }
			break;    
		case 3:  
			if(m_lastfocusItem ==MAIN_MENU_STATE)//now in main menu
			{
				printf("credits menu selected!\n");
				m_lastfocusItem = CREDITS_STATE;
				return CREDITS_STATE;
			}
			break;     
		case 4: 
			if(m_lastfocusItem ==MAIN_MENU_STATE)//now in main menu
			{
				printf("quit state selected!\n");
				m_lastfocusItem = QUIT_STATE;
				return QUIT_STATE;
			}
			break;   
		default:
			break;

		}

	}

    return 0;
}

bool MenuHandler::OnEvent(const SEvent &event) {
    // Remember the mouse state
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        switch (event.MouseInput.Event) {
            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.mouseDownPos.X = event.MouseInput.X;
                MouseState.mouseDownPos.Y = event.MouseInput.Y;
                //when mouse down, set isMouseDown to be true
                MouseState.isMouseUp = false;
                MouseState.mouseCurPos.X = event.MouseInput.X;
                MouseState.mouseCurPos.Y = event.MouseInput.Y;
				m_bSelect = false;
                break;
            case EMIE_LMOUSE_LEFT_UP:
                //when mouse up, set isMouseDown to be false
                MouseState.isMouseUp = true;
                for (u32 i = 0; i < imgAmt; ++i) {
                    //if mouse pos is within imgPos
                    if (event.MouseInput.X > imgPos[i].X &&
                            event.MouseInput.X < imgPos[i].X + imgSize.getWidth() &&
                            event.MouseInput.Y > imgPos[i].Y &&
                            event.MouseInput.Y < imgPos[i].Y + imgSize.getHeight()) {
                        //if is not the same as before, reactivate it
                            if (m_focusItem != i) {
                                m_focusItem = i;
                                LoadImage(i);
                                drawScene();
							}
						m_bSelect = true;
                        break;
                    }
                }
                break;
            case EMIE_MOUSE_MOVED:
                //when mouse move, if is mouseDown, remember where
                if (!MouseState.isMouseUp) {
                    for (u32 i = 0; i < imgAmt; ++i) {
                        //if mouse pos is within imgPos
                        if (event.MouseInput.X > imgPos[i].X &&
                                event.MouseInput.X < imgPos[i].X + imgSize.getWidth() &&
                                event.MouseInput.Y > imgPos[i].Y &&
                                event.MouseInput.Y < imgPos[i].Y + imgSize.getHeight()) {
                            //if is not the same as before, reactivate it
                            if (m_focusItem != i) {
                                m_focusItem = i;
                                LoadImage(i);
                                drawScene();
							}
							m_bSelect = true;
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
