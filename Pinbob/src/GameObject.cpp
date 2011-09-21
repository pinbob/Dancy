/*
 * GameObject.cpp
 *
 *  Created on: Jul 24, 2011
 *      Author: yejiabin
 */

#include "GameObject.h"
#include "GameOverState.h"
#include "Config.h"

GameObject::GameObject(IrrlichtDevice* pDevice, StateMachine* pStateMachine,
		u32 startTime) :
		IState(pDevice, pStateMachine), lastHit(0), comboLast(0) {
	device = pDevice;
	driver = pDevice->getVideoDriver();
	smgr = pDevice->getSceneManager();
	guienv = pDevice->getGUIEnvironment();
	then = 0;
	device->setEventReceiver(&eventListener);
	lastScore = 99999; // the max score
	// temporarily set a single song
	songcollection = new SongCollection();
	songcollection->LoadSongs("asset/songs");
	this->currentSong = &songcollection->GetSong(0);
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
	eventListener.setStatus(IG_UPDATE);
	//FIXME I don't know why should put more arguments
	logic = new DefaultGameLogic(then, new ArManager(device, smgr, driver),
			&gameInfo, soundEngine, this, this->currentSong);
}

/* This method is called by the state machine on state deactivation. Must be implemented in subclass
 * @param pNext the next active state */
void GameObject::deactivate(IState* pNext) {
	soundEngine->drop();
	m_pDevice->getSceneManager()->clear();
	m_pDevice->getCursorControl()->setVisible(true);
	m_pGuienv->clear();
}

/*  This method is called by the state manager on each form.
 *  @return "0" is no state change is wanted, "index of new state-1" to switch to another state, out of bounds index to quit program */
u32 GameObject::update(void) {
	u32 retval = 0;
	const u32 now = device->getTimer()->getTime();
	const u32 delta = now - then;
	then = now;
	driver->beginScene(true, true, 0);
	lastHit = eventListener.getHitStatus();
	int res = logic->update(delta, now, lastHit);
	switch (res) {
	case IG_DETECT:
		break;
	case IG_UPDATE:
		if (detectImage->isVisible()) {
			detectImage->setVisible(false);
		}
		for (int i = 0; i < 4; i++) {
			if (lastHit & (1 << i)) {
				widgets[i + 1]->setVisible(false);
				widgets[i + 5]->setVisible(true);
			} else {
				widgets[i + 1]->setVisible(true);
				widgets[i + 5]->setVisible(false);
			}
		}
		_updateScore(gameInfo.getScore()->getScore());
		_updateCombo(delta);
		break;
	case IG_PAUSE:
		eventListener.setStatus(IG_PAUSE);
		if ((retval = _showPauseMenu()) != 0) {
			logic->close();
			//return retval;
		}
		break;
	case IG_GAMEOVER:
		retval = GAME_OVER_STATE;
		m_pStateMachine->m_pGameOverState->setGameInfo(&gameInfo);
		break;
	default:
		break;
	}
	m_pStateMachine->setDrawScene(false);

	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();

	return retval;
}

void GameObject::_updateCombo(u32 delta) {
	u32 combo = this->gameInfo.getScore()->getCombo();
	if (combo == 0) {
		xSign->setVisible(false);
		for (int i = 0; i < COMBO_WIDTH; i++) {
			this->combo[i]->setVisible(false);
		}
		comboLast = 2500;
	} else {
		if (comboLast < 0) {
			comboLast = 2500;
			xSign->setVisible(false);
			for (int i = 0; i < COMBO_WIDTH; i++) {
				this->combo[i]->setVisible(false);
			}
		} else if (combo > 1) {
			xSign->setVisible(true);
			int counter = 0;
			if (combo > 999) {
				combo = 999;
			}
			for (int i = 100; i > 0; i /= 10) {
				if ((combo / i != 0 && counter == 0) || counter != 0) {
					this->combo[counter]->setVisible(true);
					this->combo[counter]->setImage(digits[combo / i]);
					combo -= (combo / i) * i;
					counter++;
				}
			}
		}
		comboLast -= delta;
	}
}

u32 GameObject::_showPauseMenu() {
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
		// printf("in click state, lastHit is %d\n", lastHit);
		switch (lastHit & (~CLICK_STATE)) {
		case GP_CONTINUE:
			// resume the game
			logic->setState(IG_UPDATE);
			eventListener.setStatus(IG_UPDATE);
			_hidePauseMenu();
			lastHit = 0;
			break;
		case GP_RESTART:
			return START_GAME;
			break;
		case GP_MAIN_MENU:
			return MAIN_MENU_STATE;
			break;
		default:
			break;
		}
		lastHit = 0;
	}
	return 0;
}

void GameObject::_initMenu() {
	/* menu items */
	for (int i = 0; i < GAME_MENU_LENGTH; i++) {
		widgets[i] = guienv->addImage(
				driver->getTexture(GAME_MENU_CONFIG[i].filename),
				vector2d<signed int>(GAME_MENU_CONFIG[i].position), true, 0);
		if (i >= UP_LEFT_AREA_PRESSED) {
			widgets[i]->setVisible(false);
		}
	}
	/* the score */
	guienv->addImage(driver->getTexture("asset/images/score.png"),
			vector2d<s32>(10, 10), true, 0);
	char digitFile[19] = "asset/images/x.png";
	xSign = guienv->addImage(rect<s32>(490, 30, 530, 70));
	xSign->setImage(driver->getTexture(digitFile));
	xSign->setScaleImage(true);
	xSign->setUseAlphaChannel(true);
	xSign->setVisible(false);
	for (int i = 0; i < 10; i++) {
		digitFile[13] = static_cast<char>(i + '0');digits[i] = driver->getTexture(digitFile);
	}

	for (int i = 0; i < COMBO_WIDTH; i++) {
		combo[i] = guienv->addImage(
				rect<s32>(540 + i * 25, 25, 565 + i * 25, 60), 0);
		combo[i]->setScaleImage(true);
		combo[i]->setUseAlphaChannel(true);
		combo[i]->setVisible(false);
	}

	for (int i = 0; i < SCORE_WIDTH; i++) {
		score[i] = guienv->addImage(
				rect<s32>(120 + i * 25, 5, 145 + i * 25, 40), 0);
		score[i]->setScaleImage(true);
		score[i]->setUseAlphaChannel(true);
	}
	_updateScore(0);

	/* detect the marker */
	detectImage = guienv->addImage(
			driver->getTexture("asset/images/detect.png"),
			vector2d<s32>((SCREEN_WIDTH - DETECT_WIDTH) / 2, (SCREEN_HEIGHT - DETECT_HEIGHT) / 2), true);

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
}

