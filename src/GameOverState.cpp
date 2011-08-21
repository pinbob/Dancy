/*
 * GameOverState.cpp
 *
 *  Created on: Aug 21, 2011
 *      Author: yejiabin
 */

#include "GameOverState.h"

GameOverState::GameOverState(IrrlichtDevice *pDevice,
		StateMachine *pStateMachine) :
		IState(pDevice, pStateMachine), back(0), currentInfo(0), ret(0) {

}

u32 GameOverState::update() {

	return ret;
}

void GameOverState::activate(IState* pPrevious) {
	m_pStateMachine->setDrawScene(true);
	m_pDevice->setEventReceiver(this);
	_init();
}

void GameOverState::deactivate(IState* pNext) {
	m_pDevice->getSceneManager()->clear();
	m_pGuienv->clear();
}

bool GameOverState::OnEvent(const SEvent& event) {
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_LEFT_UP:
			//when mouse up, set isMouseDown to be false
			MouseState.isMouseUp = true;
			if (event.MouseInput.X < 460 && event.MouseInput.Y > 220
					&& event.MouseInput.Y > 400 && event.MouseInput.Y < 450) {
				ret = MAIN_MENU_STATE;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

GameOverState::~GameOverState() {
}

void GameOverState::_init() {
	printf("gover\n");
	m_pGuienv->addImage(m_pDriver->getTexture("asset/images/back.png"),
			core::position2d<s32>(0, 0), -1, 0);
	m_pGuienv->addImage(
			m_pDriver->getTexture("asset/images/main_menu/title.png"),
			core::position2d<s32>(120, 10), -1, 0);
	m_pGuienv->addImage(
			m_pDriver->getTexture("asset/images/credits_menu/back1.png"),
			core::position2d<s32>(220, 400), -1, 0);
	if (currentInfo) {
		char* digitFileName = (char*) malloc(strlen("asset/images/1.png") + 1);
		for (int i = 0; i < 10; i++) {
			sprintf(digitFileName, "asset/images/%d.png", i);
			digit[i] = m_pDriver->getTexture(digitFileName);
		}
		free(digitFileName);
		IGUIImage* imgs[5];
		for (int i = 0; i < 5; i++) {
			imgs[i] = m_pGuienv->addImage(
					rect<s32>(200, 100 + i * 50, 300, 150 + i * 50));
			imgs[i]->setScaleImage(true);
			imgs[i]->setUseAlphaChannel(true);
			imgs[i]->setImage(m_pDriver->getTexture(goverImage[i]));

		}
		_showScore(0, currentInfo->getScore()->getPerfectCount());
		_showScore(1, currentInfo->getScore()->getWellDoneCount());
		_showScore(2, currentInfo->getScore()->getGoodCount());
		_showScore(3, currentInfo->getScore()->getBadCount());
		_showScore(4, currentInfo->getScore()->getMissedCount());
		IGUIImage* slots[3];
		for (int i = 0; i < 3; i++) {
			slots[i] = m_pGuienv->addImage(
					rect<s32>(380 + i * 25, 20, 410 + i * 25, 70));
		}
		u32 base =
				currentInfo->getScore()->getScore() > 999 ?
						999 : currentInfo->getScore()->getScore();
		for (int i = 100, j = 0; i > 0; i /= 10, j++) {
			slots[j]->setImage(digit[base / i]);
			slots[j]->setScaleImage(true);
			slots[j]->setUseAlphaChannel(true);
			base -= (base / i) * i;
		}
	} else {
		// This should never happen
	}
}

void GameOverState::_showScore(int idx, u32 score) {
	IGUIImage* slots[3];
	for (int i = 0; i < 3; i++) {
		slots[i] = m_pGuienv->addImage(
				rect<s32>(350 + i * 25, 100 + idx * 50, 380 + i * 25,
						150 + idx * 50));
	}
	u32 base = score > 999 ? 999 : score;
	for (int i = 100, j = 0; i > 0; i /= 10, j++) {
		slots[j]->setImage(digit[base / i]);
		slots[j]->setScaleImage(true);
		slots[j]->setUseAlphaChannel(true);
		base -= (base / i) * i;
	}
}
