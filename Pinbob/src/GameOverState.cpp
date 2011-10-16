/*
 * GameOverState.cpp
 *
 *  Created on: Aug 21, 2011
 *      Author: yejiabin
 */

#include "GameOverState.h"
#include "MenuHandler.h"

GameOverState::GameOverState(IrrlichtDevice *pDevice,
		StateMachine *pStateMachine) :
		IState(pDevice, pStateMachine), back(0), currentInfo(0), ret(0) {
	swidth = SCREEN_WIDTH;
	sheight = SCREEN_HEIGHT;
}

u32 GameOverState::update() {

	return ret;
}

void GameOverState::activate(IState* pPrevious) {
	ret = 0;
	m_pStateMachine->setDrawScene(true);
	m_pDevice->setEventReceiver(this);
	_init();
}

void GameOverState::deactivate(IState* pNext) {
	MenuHandler::m_lastfocusItem = MAIN_MENU_STATE;
	m_pDevice->getSceneManager()->clear();
	m_pGuienv->clear();
}

bool GameOverState::OnEvent(const SEvent& event) {
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_LEFT_UP:
			//when mouse up, set isMouseDown to be false
			MouseState.isMouseUp = true;
			if (event.MouseInput.X < swidth*.71875 && event.MouseInput.X > swidth*.34375
					&& event.MouseInput.Y > sheight*.8333 && event.MouseInput.Y < sheight*.9375) {
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
			core::position2d<s32>(.2*swidth, 30), -1, 0);
	m_pGuienv->addImage(
			m_pDriver->getTexture("asset/images/credits_menu/back1.png"),
			core::position2d<s32>(.45*swidth, .83*sheight), -1, 0);
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
					rect<s32>(.2125*swidth, .2*sheight + i * 50, .45*swidth, .32*sheight + i * 50));
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
					rect<s32>(.55*swidth + i * 80, 40, .65*swidth + i * 80, 110));
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
				rect<s32>(.55 * swidth + i * 80, .2*sheight + idx * 50, .65 * swidth + i * 80,
						.32*sheight + idx * 50));
	}
	u32 base = score > 999 ? 999 : score;
	for (int i = 100, j = 0; i > 0; i /= 10, j++) {
		slots[j]->setImage(digit[base / i]);
		slots[j]->setScaleImage(true);
		slots[j]->setUseAlphaChannel(true);
		base -= (base / i) * i;
	}
}
