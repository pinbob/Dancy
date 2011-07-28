
/***********************************************************************
 * Module:  StateMachine.cpp
 * Author:  liwenhaosuper
 * Modified: 2011��07��21�� 16:39:14
 * Purpose: Declaration of the class StateMachine
 ***********************************************************************/
#include <iostream>
using namespace std;

#include "StateMachine.h"
#include "irrKlang.h"
#include "irrlicht.h"
#include "ConfigFileManager.h"
#include "MenuHandler.h"
#include "SettingHandler.h"
#include "MenuFactory.h"
#include "GameObject.h"
#ifdef WIN32
#include <Windows.h>
#endif

#define TEST_GAME

StateMachine::StateMachine()
{
	m_pActive=NULL;
	m_bDrawScene=true;
	m_pMenu = new MenuHandler*[12];
	
}

StateMachine::~StateMachine(){
    delete []m_pMenu;
}

void StateMachine::initStates( IrrlichtDevice *pDevice )
{
	//init our members
	m_pDevice=pDevice;
	m_pDriver=m_pDevice->getVideoDriver();
	m_pSmgr  =m_pDevice->getSceneManager();
	m_pGuienv=m_pDevice->getGUIEnvironment();

	//create a new scene manager for the level preview
	m_pPreviewManager=m_pSmgr->createNewSceneManager(false);

	//make sure no old (already deleted) config file readers or writers are stored
	ConfigFileManager::getSharedInstance()->clearReadersWriters();

#ifdef TEST_ALL
	//now create all of the main states, set their index number and add them to the array
	m_pMenu[IState::MAIN_MENU_STATE] = 
		MenuFactory::createMenuHandler(m_pDevice, this, IState::MAIN_MENU_STATE);
	addState(m_pMenu[IState::MAIN_MENU_STATE]);    //1

        m_pMenu[IState::MODE_STATE] = 
                MenuFactory::createMenuHandler(m_pDevice, this, IState::MODE_STATE);
	addState(m_pMenu[IState::MODE_STATE]);//2
        
         m_pMenu[IState::SONG_STATE] = 
                 MenuFactory::createMenuHandler(m_pDevice, this, IState::SONG_STATE);
 	addState(m_pMenu[IState::SONG_STATE]);//3
         
	m_pGameObj = new GameObject(m_pDevice,this,1000);
	addState(m_pGameObj); //4
        
	//add more states here

	
	//first of all,activate the main menu state
	m_pActive=m_pMenu[IState::MAIN_MENU_STATE];
	//m_pActive = m_pGameObj;
#elif defined TEST_GAME
	m_pGameObj = new GameObject(m_pDevice,this,1000);
		addState(m_pGameObj); //4
	m_pActive=m_pGameObj;
//	m_pActive=m_pMenu[IState::START_GAME];
#endif
	//Let's create something for sound
	//m_pSndEngine=irrklang::createIrrKlangDevice();


	//activate the active state
	m_pActive->activate(NULL);

	ConfigFileManager::getSharedInstance()->loadConfig(m_pDevice,"asset/conf/SettingManager.xml");

}

void StateMachine::clearStates()
{
	//in this method we remove all states from the various lists they are in
	for (u32 i=0; i<m_aStates.size(); i++) delete m_aStates[i];
	    m_aStates.clear();
}

void StateMachine::graphicsChanged()
{
	 m_bGraphicsChanged=true;
}

void StateMachine::setDrawScene( bool b )
{
	m_bDrawScene=b;
}
/*
ISoundEngine * StateMachine::getSoundEngine()
{
	return m_pSndEngine;
}
*/
irr::u32 StateMachine::run()
{
	bool bQuit,bSettings=false;
	s32 lastFPS=-1;
	m_bGraphicsChanged=false;
	//load device from setting files
	
//#ifdef WIN32
//	SettingHandler *setup = new SettingHandler("asset/conf/Device.xml");
//	m_pDevice = setup->createDeviceFromSettings();
//	delete setup;
//#else 
	m_pDevice = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
		false, false, false, 0);//setup->createDeviceFromSettings();
//#endif

	m_pDevice->setWindowCaption(L"PinBob");
	//main loop
 	do { 
 		m_pDevice->setWindowCaption(L"PinBob");
 		initStates(m_pDevice);
 		m_bGraphicsChanged=false;
 		bQuit=false;
 
 		//This loop will run until the game is quit or the graphics mode is to be re-inited
 		while(m_pDevice->run() && !bQuit && !m_bGraphicsChanged) {
 			//m_bDrawScene is "false" if the active state wants to do all the drawing stuff on it's own
			//if the active state wants to do all the drawing stuff,just set call" setDrawScene(false)"
 			if (m_bDrawScene&&m_pDevice->isWindowActive()) {
 				m_pDriver->beginScene(true,true,SColor(0,200,200,200));
 				m_pSmgr->drawAll();
 				m_pGuienv->drawAll();
 				m_pDriver->endScene();
 			}
 			s32 fps=m_pDriver->getFPS();
 
 			if (lastFPS != fps) {
 				m_iFps=fps;
 				core::stringw str = L"Dancy [";
 				str += m_pDriver->getName();
 				str += "] FPS:";
 				str += fps;
 
 				m_pDevice->setWindowCaption(str.c_str());
 				lastFPS = fps;
 			}
 
 			u32 iRet=m_pActive?m_pActive->update():0;
 
 			//a return value of "0" from the active state shows that no state change is made
 			if (iRet) {
 				//the index of the state to be changed to is the return value -1 (remember: "0" means "no change")
 				iRet--;
 				//an out of bounds index is interpreted as "quit program" signal
 				if (iRet<m_aStates.size()) {
 					//get the next state
 					IState *pNext=m_aStates[iRet];
 					//deactivate the current state
 					m_pActive->deactivate(pNext);
 					//activate the next state
 					pNext->activate(m_pActive);
 					//save config file on each state change
 					ConfigFileManager::getSharedInstance()->writeConfig(m_pDevice,"asset/conf/SettingManager.xml");
 					m_pActive=pNext;
 				}
 				else bQuit=true;
 			}
 		}
 		if (m_pActive){
                    m_pActive->deactivate(NULL);
                }
 		clearStates();
 		//CShadowManager::getSharedInstance()->clear();
 		m_pSmgr->getMeshCache()->clear();
 		m_pDevice->closeDevice();
 		m_pDevice->drop();
 	}
 	while (m_bGraphicsChanged);
	return 0;
}

irr::f32 StateMachine::getAspectRatio()
{
	core::rect<s32> viewPort=m_pDriver->getViewPort();
	return 1.0f*viewPort.getWidth()/viewPort.getHeight();
}

ISceneManager * StateMachine::getPreviewSceneManager()
{
	return m_pPreviewManager;
}

irr::u32 StateMachine::getFps()
{
	 return m_iFps;
}

void StateMachine::addState( IState *pState )
{
	pState->setNum(m_aStates.size());
	m_aStates.push_back(pState);
}
