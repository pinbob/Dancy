/*
 * GameObject.cpp
 *
 *  Created on: Jul 24, 2011
 *      Author: yejiabin
 */

#include "GameObject.h"

GameObject::GameObject(IrrlichtDevice* pDevice, StateMachine* pStateMachine,
		u32 startTime) :
		IState(pDevice, pStateMachine), lastHit(0) {
	device = pDevice;
	driver = pStateMachine->m_pDriver;
	smgr = pStateMachine->m_pSmgr;
	guienv = pStateMachine->m_pGuienv;
	then = 0;
	device->setEventReceiver(&eventListener);
	_initMenu();
}

void GameObject::activate(IState* pPrevious) {
	// suppose actice time is start tiem
	then = device->getTimer()->getTime();
	logic = new DefaultGameLogic(then, new ArManager(device, smgr, driver));
}

/* This method is called by the state machine on state deactivation. Must be implemented in subclass
 * @param pNext the next active state */
void GameObject::deactivate(IState* pNext) {

}

/*  This method is called by the state manager on each form.
 *  @return "0" is no state change is wanted, "index of new state-1" to switch to another state, out of bounds index to quit program */
u32 GameObject::update(void) {
	const u32 now = device->getTimer()->getTime();
	const u32 delta = now - then;
	then = now;

	// TODO no handler for hit
	driver->beginScene(true, true, SColor(0, 200, 200, 200));
	if (eventListener.getMousePressed()
			&& lastHit != eventListener.getHitStatus()) {
		lastHit = eventListener.getHitStatus();
	} else {
		lastHit = 0;
	}
	logic->update(delta, now,lastHit);
	for (int i = 0; i < GAME_MENU_LENGTH; i++) {
		driver->draw2DImage(widgets[i], GAME_MENU_CONFIG[i].position,
				GAME_MENU_CONFIG[i].size, 0, video::SColor(255, 255, 255, 255),
				true);
	}

	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();

	return 0;
}

void GameObject::_initMenu() {
	widgets = new ITexture*[GAME_MENU_LENGTH];
	for (int i = 0; i < GAME_MENU_LENGTH; i++) {
		widgets[i] = driver->getTexture(GAME_MENU_CONFIG[i].filename);
	}
}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
	delete[] widgets;
}

