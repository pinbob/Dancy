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
	lastScore = 99999; // the max score
	_initMenu();
}

void GameObject::activate(IState* pPrevious) {
	// suppose actice time is start tiem
	then = device->getTimer()->getTime();
	logic = new DefaultGameLogic(then, new ArManager(device, smgr, driver),
			&gameInfo);
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
	//printf("lasthit %d, now %d. \n", lastHit, eventListener.getMousePressed());
	if (eventListener.getMousePressed()) {
		lastHit = eventListener.getHitStatus();
	} else {
		lastHit = 0;
	}
	logic->update(delta, now, lastHit);
	_updateScore(gameInfo.getScore()->getScore());
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();

	return 0;
}

void GameObject::_initMenu() {
	widgets = new ITexture*[GAME_MENU_LENGTH];
	for (int i = 0; i < GAME_MENU_LENGTH; i++) {
		widgets[i] = driver->getTexture(GAME_MENU_CONFIG[i].filename);
		guienv->addImage(widgets[i],
				vector2d<signed int>(GAME_MENU_CONFIG[i].position), true, 0);
	}
	guienv->addImage(driver->getTexture("asset/images/score.png"),
			vector2d<s32>(10, 10), true, 0);
	char digitFile[19] = "asset/images/x.png";
	for (int i = 0; i < 10; i++) {
		digitFile[13] = static_cast<char>(i + '0');digits[i] = driver->getTexture(digitFile);
	}
	for (int i = 0; i < SCORE_WIDTH; i++) {
		score[i] = guienv->addImage(
				rect<s32>(120 + i * 25, 5, 145 + i * 25, 40), 0);
		score[i]->setScaleImage(true);
		score[i]->setUseAlphaChannel(true);
	}
	_updateScore(0);
}

void GameObject::_updateScore(u32 score) {
	if (score != lastScore) {
		if (score > 99999) {
			score = 99999;
		}
		for (unsigned int i = 10000, j = 0; i > 0; i /= 10, j++) {
			this->score[j]->setImage(digits[score / i]);
			score -= (score/i)*i;
		}
	}
	lastScore = score;
}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
	delete[] widgets;
}

