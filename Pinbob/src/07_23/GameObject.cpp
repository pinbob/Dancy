/***********************************************************************
 * Module:  GameObject.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 23:49:42
 * Purpose: Declaration of the class GameObject
 * Comment: This class handles all player-specific stuff. It controls the AR, the camera and the player specific GUI elements
 ***********************************************************************/

#include "GameObject.h"
#include "CGameLogic.h"


GameObject::GameObject(IrrlichtDevice *pDevice, StateMachine *pStateMachine):IState(pDevice,pStateMachine)
{
	//register
	SetGameLogic(new CGameLogic());
	m_pLogic->setGame(this);
}

void GameObject::InitGameObject()
{

}

ISoundEngine * GameObject::getSoundEngine()
{
	return m_pSndEngine;
}

irr::u32 GameObject::update( void )
{
	m_pLogic->update();
	list<GUIElementToToggle *>::Iterator it;
	for (it=m_lElementsToToggle.begin(); it!=m_lElementsToToggle.end(); it++) {
		if (m_pTimer->getTime()>(*it)->m_iRemoveTime) {
			IGUIElement *pElement=(*it)->m_pElement;
			pElement->setVisible((*it)->m_bVisible);
			GUIElementToToggle *pToRemove=*it;
			m_lElementsToToggle.erase(it);
			delete pToRemove;
			break;
		}
	}
	//draw here
	m_pDriver->beginScene();
	m_pGuienv->drawAll();
	m_pSmgr->drawAll();
	m_pDriver->endScene();

	return m_bQuitGame?m_iNextState:0;
}

 bool GameObject::OnEvent( const SEvent& event ) 
 {
	 return false;
 }

 void  GameObject::deactivate( IState* pNext )
 {
	 m_pSmgr->clear();
	 m_pGuienv->clear();
	 m_pStateMachine->setDrawScene(true);
	 m_pDevice->getCursorControl()->setVisible(true);
	 m_aCountdown.clear();
	 list<GUIElementToToggle *>::Iterator it;
	 while (m_lElementsToToggle.getSize()>0) {
		 it=m_lElementsToToggle.begin();
		 GUIElementToToggle *tgl=(*it);
		 m_lElementsToToggle.erase(it);
		 delete tgl;
	 }
 }

 void GameObject::activate( IState* pPrevious )
 {
	 printf("GameObject::activate start\n");
	 //set next state
	 m_iNextState=pPrevious->getNum()+1;
	 //set sound engine
	 m_pSndEngine=m_pStateMachine->getSoundEngine();
	 m_pDevice->getCursorControl()->setVisible(true);
	 m_pDevice->setEventReceiver(this);
	 //add count down texture
	 for (s32 i=1; i<5; i++) {
		 c8 sName[0xFF];
		 sprintf(sName,"asset/images/count-down/%i.png",i);
		 ITexture *tex=m_pDriver->getTexture(sName);
		 m_aCountdown.push_back(tex);
	 }
	 //timer
	 m_pTimer=m_pDevice->getTimer();
	 while (m_pTimer->isStopped()) m_pTimer->start();
	 m_bQuitGame=false; 
	 s32 cx=m_pDriver->getScreenSize().Width/2,cy=m_pDriver->getScreenSize().Height/2;
	 m_pCountdown = m_pGuienv->addImage(rect<s32>(cx-44,cy-20,cx+44,cy+20));
	 m_pCountdown->setVisible(false);
	 m_pCountdown->setUseAlphaChannel(true);
	 //draw game scene myself
	 m_pStateMachine->setDrawScene(false);
	 m_pLogic->setTimer(m_pTimer);
	 m_pLogic->init();
 }

 GameObject::~GameObject()
 {

 }

 void GameObject::toggleCountdown( u32 iState )
 {
	 if (iState<m_aCountdown.size()) {
	     if (m_pSndEngine) m_pSndEngine->play2D("asset/sound/countdown.ogg");
	     m_pCountdown->setImage(m_aCountdown[iState]);
	     m_pCountdown->setVisible(true);
	     //more?
	     if (iState==m_aCountdown.size()-1) {
		    addElementToToggle(m_pCountdown,m_pTimer->getTime()+3000,false);
	     }
	 }
	 else m_pCountdown->setVisible(false);
 }

 void GameObject::addElementToToggle( IGUIElement *pElement, u32 iTime, bool bVisible )
 {
	 list<GUIElementToToggle *>::Iterator it;
	 for (it=m_lElementsToToggle.begin(); it!=m_lElementsToToggle.end(); it++)
		 if ((*it)->m_pElement==pElement) {
			 (*it)->m_iRemoveTime=iTime;
			 return;
		 }
	GUIElementToToggle *pRemove=new GUIElementToToggle(pElement,iTime,bVisible);
	m_lElementsToToggle.push_back(pRemove);
 }
