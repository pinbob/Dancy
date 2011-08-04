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
	driver = pDevice->getVideoDriver();
	smgr = pDevice->getSceneManager();
	guienv = pDevice->getGUIEnvironment();
	then = 0;
	device->setEventReceiver(&eventListener);
	lastScore = 99999; // the max score

}

void GameObject::activate(IState* pPrevious) {
	// suppose actice time is start tiem
	device->setEventReceiver(&eventListener);
	_initMenu();
	then = device->getTimer()->getTime();

	soundEngine = createIrrKlangDevice();
	if (!soundEngine) {
		throw int(1); // TODO handle exception later
	}
	logic = new DefaultGameLogic(then, new ArManager(device, smgr, driver),
			&gameInfo, soundEngine, this);
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
	driver->beginScene(true, true, 0); // SColor(0, 255, 255, 255));
	//printf("lasthit %d, now %d. \n", lastHit, eventListener.getMousePressed());
	//if (eventListener.getMousePressed()) {
	printf("last hit %d, \n", lastHit);
	//switch (eventListener.getHitStatus())
	//scene::ICameraSceneNode* camera = smgr->addCameraSceneNode();
	//	camera->setPosition(core::vector3df(-200, 200, -200));
	lastHit = eventListener.getHitStatus();
	int res = logic->update(delta, now, lastHit);
	//printf("update result %d.\n", res);

//	driver->draw2DImage(driver->getTexture("asset/images/perfect.png"),
//			rect<s32>(120,140,520,340), rect < s32 > (0,0,400, 200),
//			0, &SColor(255, 255, 255, 255), true);
	switch (res) {
	case IG_UPDATE:
		for (int i=0; i<4; i++) {
			if (lastHit & (1<<i)) {
				widgets[i+1]->setVisible(false);
				widgets[i+5]->setVisible(true);
			} else {
				widgets[i+1]->setVisible(true);
				widgets[i+5]->setVisible(false);
			}
		}
		_updateScore(gameInfo.getScore()->getScore());
		break;
	case IG_PAUSE:
		eventListener.setStatus(IG_PAUSE);
		_showPauseMenu();
		break;
	default:
		break;
	}
	m_pStateMachine->setDrawScene(false);

	IImage* img = driver->createImage(driver->getTexture("asset/images/perfect.tga"),
			vector2d<s32>(120, 140), dimension2d<u32>(400, 200));

//	driver->draw2DImage(driver->getTexture("asset/images/perfect.tga"),
//			rect<s32>(120, 140, 520, 340), rect<s32>(0, 0, 400, 200), 0,
//			&SColor(255, 255, 255, 255), true);
	//img->copyToScaling(hitImage,100,200);
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();

	return 0;
}

void GameObject::_showPauseMenu() {
	for (int i = 0; i < GP_LENGTH; i++) {
		//if (pauseMenu[i]->isVisible())
		//	break;
		pauseMenu[i]->setVisible(true);
		pauseMenu[i]->setColor(SColor(255, 255, 255, 255));
	}
	//printf("last hit %d .\n", lastHit);
	if (lastHit & HOVER_STATE) {
		pauseMenu[lastHit & (~HOVER_STATE)]->setColor(
				SColor(125, 255, 255, 255));
	} else if (lastHit & CLICK_STATE) {
		printf("in click state, lastHit is %d\n", lastHit);
		switch (lastHit & (~CLICK_STATE)) {
		case GP_CONTINUE:
			// resume the game
			logic->setState(IG_UPDATE);
			eventListener.setStatus(IG_UPDATE);
			_hidePauseMenu();
			lastHit = 0;
			break;
		case GP_RESTART:

			break;
		case GP_MAIN_MENU:
			break;
		default:
			break;
		}
		lastHit = 0;
	}
}

void GameObject::_initMenu() {
	/* menu items */
	for (int i = 0; i < GAME_MENU_LENGTH; i++) {
		widgets[i] =
		guienv->addImage(driver->getTexture(GAME_MENU_CONFIG[i].filename),
				vector2d<signed int>(GAME_MENU_CONFIG[i].position), true, 0);
		if (i >= UP_LEFT_AREA_PRESSED) {
			widgets[i]->setVisible(false);
		}
	}
	/* the score */
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
	/* initialize hit image */
//	for (int i=0; i< HI_LENGTH; i++) {
////		hitImage[i] = guienv->addImage(
////				driver->getTexture(HI_LAYOUT[i].filename),
////				HI_LAYOUT[i].position);
////		hitImage[i]->setVisible(false);
//		hitImage[i] = guienv->addImage(rect<s32>(120,140,520,340));
//		hitImage[i]->setScaleImage(true);
//	}
	/* pause scene */
	for (int i = 0; i < GP_LENGTH; i++) {
		pauseMenu[i] = guienv->addImage(
				driver->getTexture(GP_LAYOUT[i].filename),
				GP_LAYOUT[i].position, true, 0);
		pauseMenu[i]->setVisible(false);
	}

}

void GameObject::_updateScore(u32 score) {
	if (score != lastScore) {
		if (score > 99999) {
			score = 99999;
		}
		for (unsigned int i = 10000, j = 0; i > 0; i /= 10, j++) {
			this->score[j]->setImage(digits[score / i]);
			score -= (score / i) * i;
		}
	}
	lastScore = score;
}

void GameObject::_hidePauseMenu() {
	for (int i = 0; i < GP_LENGTH; i++) {
		//if (pauseMenu[i]->isVisible())
		//	break;
		pauseMenu[i]->setVisible(false);
	}
}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
	delete[] widgets;
}

