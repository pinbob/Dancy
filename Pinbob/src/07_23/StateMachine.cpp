
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
//#include "IrrOde.h"
#include "ConfigFileManager.h"
#include "MenuHandler.h"
//#include "GameHandler.h"
#include "SettingHandler.h"
#ifdef WIN32
#include <Windows.h>
#endif

StateMachine::StateMachine()
{
	m_pActive=NULL;
	m_bDrawScene=true;
}

void StateMachine::initStates( IrrlichtDevice *pDevice )
{
	//make sure no old (already deleted) config file readers or writers are stored
	ConfigFileManager::getSharedInstance()->clearReadersWriters();

	//now create all of the main states, set their index number and add them to the array
	/* MenuHandler(IrrlichtDevice *pDevice, StateMachine *pStateMachine,
			u32 titleWidth, u32 titleHeight, char* titlePath,
			u32 imgAmt, u32 imgWidth, u32 imgHeight, char** imgPath);
	 */
	char* imgPath[5] = {"asset/images/menu/startGame1.png", "asset/images/menu/options1.png",
			"asset/images/menu/highScores1.png", "asset/images/menu/credits1.png",
			"asset/images/menu/quit1.png"};
	m_pMenu = new MenuHandler(pDevice, this, 240, 80, "asset/images/menu/dancy.png", 5, 240, 50, imgPath);
	addState(m_pMenu);
	//m_pGame      =new GameHandler (pDevice,this);addState(m_pGame);
	
	//add more states here

	
	//first of all,activate the main menu state
	m_pActive=m_pMenu;

	//Let's create something for sound
	//m_pSndEngine=irrklang::createIrrKlangDevice();

	//init our members
	m_pDevice=pDevice;
	m_pDriver=m_pDevice->getVideoDriver();
	m_pSmgr  =m_pDevice->getSceneManager();
	m_pGuienv=m_pDevice->getGUIEnvironment();

	//create a new scene manager for the level preview
	m_pPreviewManager=m_pSmgr->createNewSceneManager(false);
	//activate the active state
	m_pActive->activate(NULL);

	ConfigFileManager::getSharedInstance()->loadConfig(m_pDevice,"asset/config/SettingManager.xml");

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
	SettingHandler *setup = new SettingHandler("asset/config/Device.xml");
	m_pDevice = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);//setup->createDeviceFromSettings();
	delete setup;
	m_pDevice->setWindowCaption(L"PinBob");
	//main loop
 	do {
 		/*
 		do {
 			//read the settings from the device settings file and create an Irrlicht device from these settings
 			SettingHandler *setup = new SettingHandler("asset/config/Device.xml");
 			m_pDevice = setup->createDeviceFromSettings();
 			bSettings=m_pDevice==NULL;
 			delete setup;
 		}while (m_pDevice==NULL);
 		*/
 
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
 					ConfigFileManager::getSharedInstance()->writeConfig(m_pDevice,"asset/config/SettingManager.xml");
 					m_pActive=pNext;
 				}
 				else bQuit=true;
 			}
 		}
 		if (m_pActive) m_pActive->deactivate(NULL);
 		cout<<"clearState\n";
 		clearStates();
 		//CShadowManager::getSharedInstance()->clear();
 		m_pSmgr->getMeshCache()->clear();
 		cout<<"closeDevice\n";
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
