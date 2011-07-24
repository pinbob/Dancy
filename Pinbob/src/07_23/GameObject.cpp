/***********************************************************************
 * Module:  GameObject.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 23:49:42
 * Purpose: Declaration of the class GameObject
 * Comment: This class handles all player-specific stuff. It controls the AR, the camera and the player specific GUI elements
 ***********************************************************************/

#include "GameObject.h"


GameObject::GameObject(IrrlichtDevice *pDevice, StateMachine *pStateMachine):IState(pDevice,pStateMachine)
{

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
	return 0;
}

 bool GameObject::OnEvent( const SEvent& event ) 
 {
	 return false;
 }

 void  GameObject::deactivate( IState* pNext )
 {

 }

 void GameObject::activate( IState* pPrevious )
 {

 }

 GameObject::~GameObject()
 {

 }
