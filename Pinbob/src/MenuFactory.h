/* 
 * File:   MenuFactory.h
 * Author: ovilia
 *
 * Created on July 26, 2011, 12:15 PM
 */

#ifndef MENUFACTORY_H
#define	MENUFACTORY_H
#include "IState.h"
#include "MenuHandler.h"

class MenuFactory{
public:
    static MenuHandler* createMenuHandler(IrrlichtDevice *pDevice, 
             StateMachine *pStateMachine, IState::StateType stateType);
};

#endif	/* MENUFACTORY_H */

